//
//  HKSWFPage.cpp
//  swfrender-ios
//
//  Created by 黄柯 on 2019/2/18.
//  Copyright © 2019年 黄柯. All rights reserved.
//

#include "HKSWFPage.hpp"
#include "assert.h"
#include "utf8.h"

extern "C" {
#include "rfxswf.h"

    fz_page *
    swf_load_page_with_reader(fz_context *ctx, fz_document *doc, void* reader, int number);
}

#define HASH_MAX 65535

extern fz_matrix swf_identity;
namespace HKSWF{
    SWFPage::SWFPage(fz_context* ctx, fz_document* doc, void* reader, int pageIndex) {
        this->ctx = ctx;
        this->doc = doc;
        this->page = swf_load_page_with_reader(ctx, doc, reader,pageIndex);
        
        createPageList();
    }
    SWFPage::~SWFPage() {
        if (this->page)
            fz_drop_page(ctx, this->page);
        
        if (page_list)
            fz_drop_display_list(ctx, page_list);
    }
    
    void SWFPage:: createPageList()
    {
        fz_display_list *list;
        fz_device *dev;
        
        fz_try(ctx)
        {
            list = fz_new_display_list(ctx);
            dev = fz_new_list_device_with_page(ctx, list, page);
            fz_run_page(ctx, page, dev, &fz_identity, NULL);
        }
        fz_always(ctx)
        {
            fz_drop_device(ctx, dev);
        }
        fz_catch(ctx)
        {
            fz_drop_display_list(ctx, list);
            fz_rethrow(ctx);
        }
        
        page_list = list;
    }
    
    fz_pixmap*  SWFPage::renderPage(int width)
    {
        fz_matrix ctm = swf_identity;
        fz_rect rect = this->page->page_rect;
        fz_irect bbox;
        fz_device *dev = NULL;
        fz_pixmap *pix = NULL;
        
        fz_try(ctx)
        {
            float scale = 2;
            //指定图片宽度，进行缩放
            if(width > 0)
            {
                //缩放比例
                scale = width / (rect.x1-rect.x0);
            }
            
            fz_scale(&ctm,scale,scale);
            rect.x1 *= scale;
            rect.y1 *= scale;
            
            fz_irect_from_rect(&bbox, &rect);
            pix = fz_new_pixmap_with_bbox(ctx, fz_device_rgb(ctx), &bbox);
            fz_clear_pixmap_with_value(ctx, pix, 255);
            
            dev = fz_new_draw_device(ctx, pix);
            fz_run_display_list(ctx, page_list, dev, &ctm, &rect, NULL);
        }
        fz_always(ctx)
        {
            fz_drop_device(ctx, dev);
        }
        fz_catch(ctx)
        {
            fz_drop_pixmap(ctx, pix);
            return NULL;
        }
        
        return pix;
    }
    
    fz_pixmap* SWFPage::contentPage(int width) {
        fz_rect view;
        fz_rect rect;
        fz_bound_page(ctx,page,&rect);
        
        float scale = width / (rect.x1-rect.x0);
        
        view = rect;
        view.x1 *= scale;
        view.y1 *= scale;
        
        fz_rect tile = page->content_rect;
        tile.x0 *= scale;
        tile.y0 *= scale;
        tile.x1 *= scale;
        tile.y1 *= scale;
        
        return tileimage(view, tile);
    }
    
    fz_pixmap* SWFPage::tileimage(fz_rect view, fz_rect tile) {
        fz_buffer* buf = 0;
        fz_matrix ctm = swf_identity;
        fz_rect rect = this->page->page_rect;
        fz_irect bbox;
        fz_device *dev = NULL;
        fz_pixmap *pix = NULL;
        
        float width = view.x1 - view.x0;
        
        fz_try(ctx)
        {
            //指定图片宽度，进行缩放
            if(width > 0)
            {
                //缩放比例
                float scale = width / (rect.x1-rect.x0);
                fz_scale(&ctm,scale,scale);
                rect.x1 *= scale;
                rect.y1 *= scale;
                printf("scale=%f\n",scale);
            }
            
            fz_irect_from_rect(&bbox, &tile);
            pix = fz_new_pixmap_with_bbox(ctx, fz_device_rgb(ctx), &bbox);
            fz_clear_pixmap_with_value(ctx, pix, 255);
            
            dev = fz_new_draw_device(ctx, pix);
            
            fz_run_display_list(ctx, page_list, dev, &ctm, &tile, NULL);
        }
        fz_always(ctx)
        {
            fz_drop_device(ctx, dev);
            fz_drop_buffer(ctx, buf);
        }
        fz_catch(ctx)
        {
            fz_drop_pixmap(ctx, pix);
            pix = 0;
            printf("render error\n");
        }
        
        return pix;
    }
    
    fz_buffer* SWFPage::getTextRect() {
//        swf_sort_lines(ctx,text_page);
        Page_Rect* text_page = (Page_Rect*)this->page->text_page;
        
        fz_buffer* buffer = fz_new_buffer(ctx, 0);
        fz_output *out = fz_new_output_with_buffer(ctx, buffer);
        
        char rectstr[256];
        
        memset(rectstr, 0, 256);
        sprintf(rectstr, "%0.2f %0.2f %0.2f %0.2f",
                this->page->page_rect.x0,
                this->page->page_rect.y0,
                this->page->page_rect.x1 - this->page->page_rect.x0,
                this->page->page_rect.y1 - this->page->page_rect.y0);
        fz_printf(ctx, out, "%s\n\n",rectstr);

        memset(rectstr, 0, 256);
        sprintf(rectstr, "%0.2f %0.2f %0.2f %0.2f",
                this->page->content_rect.x0,
                this->page->content_rect.y0,
                this->page->content_rect.x1 - this->page->content_rect.x0,
                this->page->content_rect.y1 - this->page->content_rect.y0);
        fz_printf(ctx, out, "%s\n\n",rectstr);
        
//        mulMapWords* hash_words[HASH_MAX];
//        for (int i = 0;i < HASH_MAX; i++) {
//            hash_words[i] = new mulMapWords();
//        }
        
        mulMapRects* hash_rects[HASH_MAX];
        for (int i = 0;i < HASH_MAX; i++) {
            hash_rects[i] = new mulMapRects();
        }
        
        mulMapRects *Tmprects;
//        mulMapWords *Tmpword;
        for (int i=0; i<text_page->len; i++) {
            Line_Rect* line = &text_page->lines[i];
            memset(rectstr, 0, 256);
            sprintf(rectstr, "%0.2f %0.2f %0.2f %0.2f",
                    line->rect.x0,
                    line->rect.y0,
                    line->rect.x1 - line->rect.x0,
                    line->rect.y1 - line->rect.y0);
            fz_printf(ctx, out, "%s\n",rectstr);
            for (int j=0; j<line->len; j++) {
                bool bSkip = false;
                Text_Rect* text = &line->texts[j];
                
                if (text->unicode >= 32 && text->unicode <= 47) {//英文标点符号
                    bSkip = true;
                }
                
//                Tmpword = hash_words[text->unicode];
                Tmprects = hash_rects[text->unicode];
                int k = rect2k(text->rect);
                if (!bSkip) {
                    if(!fz_is_empty_rect(&text->rect) && sameRect2(Tmprects, text))
                    {
                        continue;
                    }
                    else
                    {
//                        Tmpword->insert(std::make_pair(text->unicode,text->rect));
                        Tmprects->insert(std::make_pair(k,text->rect));
                    }
                }
                
//                getUTF8(text->unicode);
                memset(rectstr, 0, 256);
                sprintf(rectstr, "%0.2f %0.2f %0.2f %0.2f",
                        text->rect.x0,
                        text->rect.y0,
                        text->rect.x1 - text->rect.x0,
                        text->rect.y1 - text->rect.y0);
                fz_printf(ctx, out, "\\u%04x,%s\n",text->unicode,rectstr);
            }
            
//            printf("\n");
            fz_printf(ctx,out,"\n");
        }
        
//        for (int i=0; i<HASH_MAX; i++) {
//            delete hash_words[i];
//        }
        
        for (int i=0; i<HASH_MAX; i++) {
            delete hash_rects[i];
        }
        
        fz_drop_output(ctx, out);
        return buffer;
    }
    
    int SWFPage::rect2k(fz_rect rect)
    {
        float xm = (rect.x0 + rect.x1)/2.0;
        float ym = (rect.y0 + rect.y1)/2.0;
        float r = sqrt(xm*xm + ym*ym);
        float k = ym/xm;
        return (int)r*k;
    }
    
    fz_rect SWFPage::intersect(fz_rect rect1, fz_rect rect2)
    {
        fz_rect inter_rect = rect1;
        fz_intersect_rect(&inter_rect,&rect2);
        return inter_rect;
    }

    float SWFPage::percent(fz_rect inter,fz_rect ori)
    {
        float w = abs(inter.x1-inter.x0)/abs(ori.x1-ori.x0);
        float h = abs(inter.y1-inter.y0)/abs(ori.y1-ori.y0);
        return w * h;
    }
    
    bool SWFPage::sameRect2(mulMapRects *rects,Text_Rect* text)
    {
        mulMapRects::iterator it;
        int k = rect2k(text->rect);
        for (it=rects->equal_range(k).first; it!=rects->equal_range(k).second; ++it)
        {
            fz_rect ori = (it)->second;
            fz_rect new_rect = {0};
           if (fz_is_empty_rect(&ori))
            {
                continue;
            }
//            printf("unicode:%d ",text->unicode);
//            printf("k:%d %0.2f %0.2f %0.2f %0.2f\n",k,
//                   ori.x0,
//                   ori.y0,
//                   ori.x1,
//                   ori.y1);
            new_rect = intersect(ori,text->rect);
            if(percent(new_rect,ori) > 0.8)
            {
                
                return true;
            }
        }
        return false;
    }

    bool SWFPage::sameRect(mulMapWords *words,Text_Rect* text)
    {
        mulMapWords::iterator it;
        for (it=words->begin();it != words->end();it++)
        {
            fz_rect ori = (it)->second;
            unsigned short u = (it)->first;
            fz_rect new_rect = {0};
         
            new_rect = intersect(ori,text->rect);
            if(percent(new_rect,ori) > 0.8)
            {
                return true;
            }
        }
        return false;
    }
};
