/*
 * general.cc
 *
 * Handling general stuffs
 *
 * Copyright (C) 2012,2013,2014 Lu Wang <coolwanglu@gmail.com>
 */

#include <cstdio>
#include <ostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>

#include <GlobalParams.h>

#include <fofi/FoFiTrueType.h>

#include "pdf2htmlEX-config.h"
#include "Version.h"
#include "HTMLRenderer.h"
#include "HTMLTextLine.h"
#include "Base64Stream.h"

#include "BackgroundRenderer/BackgroundRenderer.h"

#include "util/namespace.h"
#include "util/ffw.h"
#include "util/math.h"
#include "util/path.h"
#include "util/css_const.h"
#include "util/encoding.h"

#include <sys/stat.h>

#include "SplashOutputDev.h"
#include "splash/SplashBitmap.h"
#include "splash/Splash.h"
#include "splash/SplashState.h"
#include "Huangke/SplashOutputDevLayer.h"
#include "util/const.h"

#include <goo/ImgWriter.h>
#include <goo/PNGWriter.h>
#include <goo/JpegWriter.h>
#include <goo/ImgWriter.h>
#include <goo/PNGWriter.h>
#include <goo/JpegWriter.h>
#include <goo/NetPBMWriter.h>
#include <goo/TiffWriter.h>
#include <sys/stat.h>
#include <JBIG2Stream.h>
#include "Version.h"

namespace pdf2htmlEX {
    
        
    using std::fixed;
    using std::flush;
    using std::ostream;
    using std::max;
    using std::min_element;
    using std::vector;
    using std::abs;
    using std::cerr;
    using std::endl;
    
    HTMLRenderer::HTMLRenderer(const Param & param)
    :OutputDev()
    ,param(param)
    ,html_text_page(param, all_manager)
    ,preprocessor(param)
    ,tmp_files(param)
    ,tracer(param)
    {
        if(!(param.debug))
        {
            //disable error messages of poppler
            globalParams->setErrQuiet(gTrue);
        }
        
        ffw_init(param.debug);
        
        cur_mapping.resize(0x10000);
        cur_mapping2.resize(0x100);
        width_list.resize(0x10000);
        
        /*
         * For these states, usually the error will not be accumulated
         * or may be handled well (whitespace_manager)
         * So we can set a large eps here
         */
        all_manager.vertical_align.set_eps(param.v_eps);
        all_manager.whitespace    .set_eps(param.h_eps);
        all_manager.left          .set_eps(param.h_eps);
        /*
         * For other states, we need accurate values
         * optimization will be done separately
         */
        all_manager.font_size   .set_eps(EPS);
        all_manager.letter_space.set_eps(EPS);
        all_manager.word_space  .set_eps(EPS);
        all_manager.height      .set_eps(EPS);
        all_manager.width       .set_eps(EPS);
        all_manager.bottom      .set_eps(EPS);
        
        tracer.on_char_drawn =
        [this](double * box) { covered_text_detector.add_char_bbox(box); };
        tracer.on_char_clipped =
        [this](double * box, bool partial) { covered_text_detector.add_char_bbox_clipped(box, partial); };
        tracer.on_non_char_drawn =
        [this](double * box) { covered_text_detector.add_non_char_bbox(box); };
    }
    
    HTMLRenderer::~HTMLRenderer()
    {
        ffw_finalize();
    }
    
    
    void test(string fontname) {
        string fontPath = "/Users/huangke/Desktop/ayou/work/other/pdf2html/pc-web/pdf2htmlEX/fonts/";
        fontPath += fontname;
        FoFiTrueType * ff = FoFiTrueType::load((char*)fontPath.c_str());
        
        int cmap = -1;
        for (int i = 0; i < ff->getNumCmaps(); ++i) {
            int cmapPlatform = ff->getCmapPlatform(i);
            int cmapEncoding = ff->getCmapEncoding(i);
            if (cmapPlatform == 3 && cmapEncoding == 10) {
                /* UCS-4 */
                cmap = i;
                /* use UCS-4 cmap */
                break;
            } else if (cmapPlatform == 3 && cmapEncoding == 1) {
                /* Unicode */
                cmap = i;
            } else if (cmapPlatform == 0 && cmap < 0) {
                cmap = i;
            }
        }
        
        std::vector<char> gids;
        gids.resize(0x10000);
        std::fill(gids.begin(), gids.end(), 0);
        
        uint range[] = {
            0x0000, 0x007F,
            0x0100, 0x017F,
            0x2000, 0x206F,
            0x2153, 0x2183,
            0x3000, 0x303F,
            0x2460, 0x24EA,
            0xFE50, 0xFE6B,
            0xFF01, 0xFFEE
        };
        
        for (int i=0;i<8;i++) {
            uint start = range[i*2];
            uint stop = range[i*2+1];
            
            for (uint u = start; u<=stop; u++) {
                Gushort gid = ff->mapCodeToGID(cmap,u);
                Gushort vgid = ff->mapToVertGID(gid);
                if (gid != 0) gids[gid] = 1;
                if (vgid != 0) gids[vgid] = 1;
            }
        }
        
        ffw_load_font(fontPath.c_str());
        ffw_prepare_font();
        
        ffw_reencode_glyph_order();
        
        ffw_reduce_font(gids.data(), 0x10000);
        
        string nfontPath = "/Users/huangke/Desktop/ayou/work/other/pdf2html/pc-web/pdf2htmlEX/fonts/hk/";
        nfontPath += fontname;
        
        ffw_save(nfontPath.c_str());
        ffw_close();
    }
    
    void HTMLRenderer::pre_process_extenal_font() {
        
        //        test("Arial Bold Italic.ttf");
        //        test("Arial Bold.ttf");
        //        test("Arial Italic.ttf");
        //        test("Arial.ttf");
        //        test("Courier New Bold Italic.ttf");
        //        test("Courier New Bold.ttf");
        //        test("Courier New Italic.ttf");
        //        test("Courier New.ttf");
        //        test("Helvetica.ttf");
        //        test("Kaiti.ttf");
        //        test("SimHei.ttf");
        //        test("SimSun-ExtB.ttf");
        //        test("SimSun.ttf");
        //        test("Symbol.ttf");
        //        test("Times New Roman Bold Italic.ttf");
        //        test("Times New Roman Bold.ttf");
        //        test("Times New Roman Italic.ttf");
        //        test("Times New Roman.ttf");
        //        test("STHUPO.ttf");
        //        test("STLITI.ttf");
        //        test("STXINWEI.ttf");
        //        test("STXINGKA.ttf");
        //        test("STZHONGS.ttf");
        
        for (std::unordered_map<std::string, Preprocessor::Localfontinfo>::const_iterator it = preprocessor.local_font_maps.begin();
             it != preprocessor.local_font_maps.end();
             it++) {
            Preprocessor::Localfontinfo fontinfo = it->second;
            
            string font_filename = (char*)str_fmt("%s/%s", param.tmp_dir.c_str(), fontinfo.fontName.c_str());
            
            struct stat stat_buf;
            if((stat(font_filename.c_str(), &stat_buf) != 0))
            {
                ffw_load_font(fontinfo.fontPath.c_str());
                ffw_prepare_font();
                
                ffw_reencode_glyph_order();
                
                std::vector<char> gids;
                gids.resize(0x10000);
                std::fill(gids.begin(), gids.end(), 0);
                int total = 0;
                for(int cur_code = 0; cur_code < std::min(0x10000, fontinfo.code2gid_len); ++cur_code)
                {
                    if(!fontinfo.usedmap[cur_code])
                        continue;
                    int gid = fontinfo.code2gids[cur_code];
                    if (gid != 0) {
                        gids[gid] = 1;
                        total ++;
                    }
                }
                
                std::cout << fontinfo.fontName <<":"<< total << endl;
                
                ffw_reduce_font(gids.data(), std::min(0x10000, fontinfo.code2gid_len));
                
                //                ffw_reencode_unicode_full();
                
                ffw_save(font_filename.c_str());
                ffw_close();
            }
        }
    }
    
    void HTMLRenderer::process(PDFDoc *doc)
    {
        cur_doc = doc;
        cur_catalog = doc->getCatalog();
        xref = doc->getXRef();
        
        
        pre_process(doc);
        
        if (param.embed_external_font) {
            pre_process_extenal_font();
        }
        
        ///////////////////
        // Process pages
        
        if(param.process_nontext)
        {
            bg_renderer = BackgroundRenderer::getBackgroundRenderer(param.bg_format, this, param);
            if(!bg_renderer)
                throw "Cannot initialize background renderer, unsupported format";
            bg_renderer->init(doc);
            
            fallback_bg_renderer = BackgroundRenderer::getFallbackBackgroundRenderer(this, param);
            if (fallback_bg_renderer)
                fallback_bg_renderer->init(doc);
        }
        
        double totalWidth = 0;
        double totalHeight = 0;
        double fitWidth = 0;
        double fitHeight = 0;
        
        int page_count = (param.last_page - param.first_page + 1);
        for(int i = param.first_page; i <= param.last_page ; ++i)
        {
            if (param.tmp_file_size_limit != -1 && tmp_files.get_total_size() > param.tmp_file_size_limit * 1024) {
                cerr << "Stop processing, reach max size\n";
                break;
            }
            
            if (0) {
                std::string progresspath = (char*)str_fmt("%s/progress.json", param.dest_dir.c_str());
                
                ofstream outf(progresspath, ofstream::binary);
                
                outf << "{";
                outf << "\"version\":" << "\"1.0\"" ;
                outf << ",\"processFont\":" << param.onlyProcessFont;
                outf << ",\"progress\":" << i;
                outf << ",\"total\":" << param.last_page;
                outf << "}";
                
                outf.close();
            }
            
            cerr << "Working: " << (i-param.first_page) << "/" << page_count << '\r' << flush;
            
            if(param.split_pages)
            {
                if (!param.onlyProcessFont) {
                    // copy the string out, since we will reuse the buffer soon
                    string filled_template_filename = (char*)str_fmt(param.page_filename.c_str(), i);
                    auto page_fn = str_fmt("%s/page/%s", param.dest_dir.c_str(), filled_template_filename.c_str());
                    f_curpage = new ofstream((char*)page_fn, ofstream::binary);
                    if(!(*f_curpage))
                        throw string("Cannot open ") + (char*)page_fn + " for writing";
                    set_stream_flags((*f_curpage));
                    
                    cur_page_filename = filled_template_filename;
                }
                
                //生成位置信息的文件
                if(param.html)
                {
                    if(!param.onlyProcessFont){
                        string filled_template_filename = (char*)str_fmt(param.position_filename.c_str(), i);
                        auto position_fn = str_fmt("%s/page/%s", param.dest_dir.c_str(), filled_template_filename.c_str());
                        
                        pos_curpage = new ofstream((char*)position_fn, ofstream::binary);
                        if(!(*pos_curpage))
                            throw string("Cannot open ") + (char*)position_fn + " for writing";
                        set_stream_flags((*pos_curpage));
                        
    //                    cur_position_filename = filled_template_filename;
                    }
                }
            }
            
            if(param.debug)
                std::cout << "displayPage " << i << " start" << endl;
            doc->displayPage(this, i,
                             text_zoom_factor() * DEFAULT_DPI, text_zoom_factor() * DEFAULT_DPI,
                             0,
                             (!(param.use_cropbox)),
                             true,  // crop
                             false, // printing
                             nullptr, nullptr, nullptr, nullptr);
            if(param.debug)
                std::cout << "displayPage " << i << " end" << endl;
            
            double curWidth = this->html_text_page.get_width();
            double curHeight = this->html_text_page.get_height();
            
            totalWidth += curWidth;
            totalHeight += curHeight;
            
            if (totalWidth != 0) {
                double aveWidth = totalWidth / i;
                
                if (abs(curWidth - aveWidth) < abs(fitWidth - aveWidth)) {
                    fitWidth = curWidth;
                    fitHeight = curHeight;
                }
            }
            
            
            if(param.split_pages)
            {
                delete f_curpage;
                f_curpage = nullptr;
                
                delete pos_curpage;
                pos_curpage = nullptr;
            }
            
        }
        if(page_count >= 0)
            cerr << "Working: " << page_count << "/" << page_count;
        cerr << endl;
        
        ////////////////////////
        // Process Outline
        if(param.process_outline)
            process_outline();
        
        post_process();
        
        bg_renderer = nullptr;
        fallback_bg_renderer = nullptr;
        
        cerr << endl;
        
        
        if (param.onlyProcessFont || param.embed_image) {
            struct stat file_buf;
            stat(param.input_filename.c_str(), &file_buf);
               
            std::string metapath = (char*)str_fmt("%s/meta.json", param.dest_dir.c_str());
            std::string tmetapath = (char*)str_fmt("%s/t_meta.json", param.dest_dir.c_str());
            
            struct stat stat_buf;
            if((stat(metapath.c_str(), &stat_buf) != 0)) {
                ofstream outf(tmetapath, ofstream::binary);
                
                outf << "{";
                outf << "\"page_count\":" << doc->getNumPages();
                outf << ",\"width\":" << fitWidth;
                outf << ",\"height\":" << fitHeight;
                outf << ",\"version\":" << "\"" << HUANGKE_VERSION << "\"";
                outf << ",\"file_size\":" << file_buf.st_size;
                outf << "}";
                
                outf.close();
                rename(tmetapath.c_str(), metapath.c_str());
            }
        }
        
    }
    
    void HTMLRenderer::setDefaultCTM(double *ctm)
    {
        memcpy(default_ctm, ctm, sizeof(default_ctm));
    }
    
    void HTMLRenderer::startPage(int pageNum, GfxState *state, XRef * xref)
    {
        covered_text_detector.reset();
        tracer.reset(state);
        
        this->pageNum = pageNum;
        html_text_page.pageNum = pageNum;
        html_text_page.set_page_size(state->getPageWidth(), state->getPageHeight());
        
        reset_state();
    }
    
    void HTMLRenderer::endPage() {
        if (param.onlyProcessFont) return;
        
        std::stringstream html_out;
        std::stringstream css_out;
        std::stringstream pos_out;
        
        set_stream_flags(html_out);
        set_stream_flags(css_out);
        set_stream_flags(pos_out);
        
        // dump all text
        html_text_page.dump_text(html_out);
        html_text_page.dump_css(css_out);
        
        int maxWidth = html_text_page.get_width()*2;        //dump the position
        int maxHight = html_text_page.get_height()*2;
        if(param.html)
        {
            char str_box[50]={0};
            sprintf(str_box, "%d,%d",maxWidth,maxHight);
            pos_out << "<div m=\""<<str_box <<"\">";
            html_text_page.dump_position(pos_out);
            pos_out << "</div>";
        }

        html_text_page.clear();
        
        //        (*f_curpage) << f_css.fs.rdbuf();
        
        (*f_curpage) << "<div class=\"__cpdf__\">\n";
        (*f_curpage) << css_out.rdbuf();
        
        
        long long wid = all_manager.width.install(html_text_page.get_width());
        long long hid = all_manager.height.install(html_text_page.get_height());
        
        
        {
            (*f_curpage)
            << "<div id=\"" << CSS::PAGE_FRAME_CN << pageNum
            << "\" class=\"" << CSS::PAGE_FRAME_CN << "\""
            << " style=\"width:" << html_text_page.get_width() << "px;" << "height:" <<html_text_page.get_height() << "px"
            << "\" data-page-no=\"" << pageNum << "\">";
            
            (*f_curpage)
            << "<div class=\"" << CSS::PAGE_CONTENT_BOX_CN
            << " " << CSS::PAGE_CONTENT_BOX_CN << pageNum << "\""
            << "\">";
        }
        
        (*f_curpage) << "<div class=\"__pdf__" << this->pageNum << "\">";
        
        /*
         * When split_pages is on, f_curpage points to the current page file
         * and we want to output empty frames in f_pages.fs
         */
        if(param.split_pages)
        {
            f_pages.fs
            << "<div id=\"" << CSS::PAGE_FRAME_CN << pageNum
            << "\" class=\"" << CSS::PAGE_FRAME_CN
            << " " << CSS::WIDTH_CN << wid
            << " " << CSS::HEIGHT_CN << hid
            << "\" data-page-no=\"" << pageNum
            << "\" data-page-url=\"";
            
            writeAttribute(f_pages.fs, "page/"+cur_page_filename);
            f_pages.fs << "\">";
        }
        
        
        //image layer
        {
            SplashColor color;
            color[0] = color[1] = color[2] = 254;
            // If the user specified "jpg" use JPEG, otherwise PNG
            SplashImageFileFormat format = strcmp(param.bg_format.c_str(), "jpg") ?
            splashFormatPng : splashFormatJpeg;
            
            SplashOutputDevLayer *splashOut = new SplashOutputDevLayer(splashModeRGB8, 4, gFalse, color);
            splashOut->param = param;
            splashOut->pageNum = pageNum;
            splashOut->startDoc(this->cur_doc);
            this->cur_doc->displayPage(splashOut, pageNum,
                                       param.h_dpi, param.v_dpi,
                                       0, (!(param.use_cropbox)), gFalse, gFalse);
            
            splashOut->image_out << "\n";
            (*f_curpage) << splashOut->image_out.rdbuf();
            
            delete splashOut;
        }
            
        if(!param.onlyProcessFont && !param.embed_image){
            if (pageNum <= 5) {
                bg_renderer->render_page(cur_doc, pageNum);
                bg_renderer->dump_image(pageNum);
            }
        }
        
        
        
        //mask layer
#ifdef __MAC_10_0
        if (0)
#else
        if (0)
#endif
            {
                if(param.process_nontext)
                {
                    if (bg_renderer->render_page(cur_doc, pageNum))
                    {
                        bg_renderer->embed_image(pageNum);
                    }
                    else if (fallback_bg_renderer)
                    {
                        if (fallback_bg_renderer->render_page(cur_doc, pageNum))
                            fallback_bg_renderer->embed_image(pageNum);
                    }
                }
            }
        
        (*f_curpage) << html_out.rdbuf();
        
        if(param.html)
        {
            (*pos_curpage)<<pos_out.rdbuf();
        }
        
        {
            // process form
            if(param.process_form)
                process_form(*f_curpage);
            
            // process links before the page is closed
            cur_doc->processLinks(this, pageNum);
            
            // close box
            (*f_curpage) << "</div>";
            
            // dump info for js
            // TODO: create a function for this
            // BE CAREFUL WITH ESCAPES
            {
                (*f_curpage) << "<div class=\"" << CSS::PAGE_DATA_CN << "\" data-data='{";
                
                //default CTM
                (*f_curpage) << "\"ctm\":[";
                for(int i = 0; i < 6; ++i)
                {
                    if(i > 0) (*f_curpage) << ",";
                    (*f_curpage) << round(default_ctm[i]);
                }
                (*f_curpage) << "]";
                
                (*f_curpage) << "}'></div>";
            }
            
            // close page
            (*f_curpage) << "</div>" << endl;
            
            if(param.split_pages)
            {
                f_pages.fs << "</div>" << endl;
            }
            
            (*f_curpage) << "</div>" << endl;
            (*f_curpage) << "</div>" << endl;
        }
        
        
    }
    
    void HTMLRenderer::pre_process(PDFDoc * doc)
    {
        preprocessor.process(doc);
        
        /*
         * determine scale factors
         */
        {
            vector<double> zoom_factors;
            
            if(is_positive(param.zoom))
            {
                zoom_factors.push_back(param.zoom);
            }
            
            if(is_positive(param.fit_width))
            {
                zoom_factors.push_back((param.fit_width) / preprocessor.get_max_width());
            }
            
            if(is_positive(param.fit_height))
            {
                zoom_factors.push_back((param.fit_height) / preprocessor.get_max_height());
            }
            
            double zoom = (zoom_factors.empty() ? 1.0 : (*min_element(zoom_factors.begin(), zoom_factors.end())));
            
            text_scale_factor1 = max<double>(zoom, param.font_size_multiplier);
            text_scale_factor2 = zoom / text_scale_factor1;
        }
        
        // we may output utf8 characters, so always use binary
        {
            /*
             * If embed-css
             * we have to keep the generated css file into a temporary place
             * and embed it into the main html later
             *
             * otherwise
             * leave it in param.dest_dir
             */
            if(!param.onlyProcessFont && !param.embed_image){
                auto fn = (param.embed_css)
                ? str_fmt("%s/__css", param.tmp_dir.c_str())
                : str_fmt("%s/%s", param.dest_dir.c_str(), param.css_filename.c_str());
                
                if(param.embed_css)
                    tmp_files.add((char*)fn);
                
                f_css.path = (char*)fn;
                f_css.fs.open(f_css.path, ofstream::binary);
                if(!f_css.fs)
                    throw string("Cannot open ") + (char*)fn + " for writing";
                set_stream_flags(f_css.fs);
            }
        }
        
        if (param.process_outline)
        {
            /*
             * The logic for outline is similar to css
             */
            
            auto fn = (param.embed_outline)
            ? str_fmt("%s/__outline", param.tmp_dir.c_str())
            : str_fmt("%s/%s", param.dest_dir.c_str(), param.outline_filename.c_str());
            
            if(param.embed_outline)
                tmp_files.add((char*)fn);
            
            f_outline.path = (char*)fn;
            f_outline.fs.open(f_outline.path, ofstream::binary);
            if(!f_outline.fs)
                throw string("Cannot open") + (char*)fn + " for writing";
            
            // might not be necessary
            set_stream_flags(f_outline.fs);
        }
        
        {
            /*
             * we have to keep the html file for pages into a temporary place
             * because we'll have to embed css before it
             *
             * Otherwise just generate it
             */
            auto fn = str_fmt("%s/__pages", param.tmp_dir.c_str());
            tmp_files.add((char*)fn);
            
            f_pages.path = (char*)fn;
            f_pages.fs.open(f_pages.path, ofstream::binary);
            if(!f_pages.fs)
                throw string("Cannot open ") + (char*)fn + " for writing";
            set_stream_flags(f_pages.fs);
        }
        
        if(param.split_pages)
        {
            f_curpage = nullptr;
            pos_curpage = nullptr;
        }
        else
        {
            f_curpage = &f_pages.fs;
            pos_curpage = &f_pages.fs;
        }
    }
    
    void HTMLRenderer::post_process(void)
    {
        //        dump_css();
        
        // close files if they opened
        if (param.process_outline)
        {
            f_outline.fs.close();
        }
        f_pages.fs.close();
        f_css.fs.close();
        if (!param.onlyProcessFont && !param.embed_image)
        {
            // build the main HTML file
            ofstream output;
            if(!param.onlyProcessFont)
            {
                auto fn = str_fmt("%s/%s", param.dest_dir.c_str(), param.output_filename.c_str());
                output.open((char*)fn, ofstream::binary);
                if(!output)
                    throw string("Cannot open ") + (char*)fn + " for writing";
                set_stream_flags(output);
            }
            
            // apply manifest
            ifstream manifest_fin((char*)str_fmt("%s/%s", param.data_dir.c_str(), MANIFEST_FILENAME.c_str()), ifstream::binary);
            if(!manifest_fin) {
                //            printf( "Cannot open the manifest file" );
                return;
            }
            
            bool embed_string = false;
            string line;
            long line_no = 0;
            while(getline(manifest_fin, line))
            {
                // trim space at both sides
                {
                    static const char * whitespaces = " \t\n\v\f\r";
                    auto idx1 = line.find_first_not_of(whitespaces);
                    if(idx1 == string::npos)
                    {
                        line.clear();
                    }
                    else
                    {
                        auto idx2 = line.find_last_not_of(whitespaces);
                        assert(idx2 >= idx1);
                        line = line.substr(idx1, idx2 - idx1 + 1);
                    }
                }
                
                ++line_no;
                
                if(line == "\"\"\"")
                {
                    embed_string = !embed_string;
                    continue;
                }
                
                if(embed_string)
                {
                    output << line << endl;
                    continue;
                }
                
                if(line.empty() || line[0] == '#')
                    continue;
                
                
                if(line[0] == '@')
                {
                    embed_file(output, param.data_dir + "/" + line.substr(1), "", true);
                    continue;
                }
                
                if(line[0] == '$')
                {
                    if(line == "$css")
                    {
                        embed_file(output, f_css.path, ".css", false);
                    }
                    else if (line == "$outline")
                    {
                        if (param.process_outline && param.embed_outline)
                        {
                            ifstream fin(f_outline.path, ifstream::binary);
                            if(!fin)
                                throw "Cannot open outline for reading";
                            output << fin.rdbuf();
                            output.clear(); // output will set fail big if fin is empty
                        }
                    }
                    else if (line == "$pages")
                    {
                        ifstream fin(f_pages.path, ifstream::binary);
                        if(!fin)
                            throw "Cannot open pages for reading";
                        output << fin.rdbuf();
                        output.clear(); // output will set fail bit if fin is empty
                    }
                    else
                    {
                        cerr << "Warning: manifest line " << line_no << ": Unknown content \"" << line << "\"" << endl;
                    }
                    continue;
                }
                
                cerr << "Warning: unknown line in manifest: " << line << endl;
            }
        }
    }
    
    void HTMLRenderer::set_stream_flags(std::ostream & out)
    {
        // we output all ID's in hex
        // browsers are not happy with scientific notations
        out << hex << fixed;
    }
    
    void HTMLRenderer::dump_css (void)
    {
        assert(0);
        //        all_manager.transform_matrix.pageIndex =
        //        all_manager.vertical_align  .pageIndex =
        //        all_manager.letter_space    .pageIndex =
        //        all_manager.stroke_color    .pageIndex =
        //        all_manager.word_space      .pageIndex =
        //        all_manager.whitespace      .pageIndex =
        //        all_manager.fill_color      .pageIndex =
        //        all_manager.font_size       .pageIndex =
        //        all_manager.bottom          .pageIndex =
        //        all_manager.height          .pageIndex =
        //        all_manager.width           .pageIndex =
        //        all_manager.left            .pageIndex =
        //        all_manager.bgimage_size    .pageIndex =
        //        param.pageIndex;
        //
        //        all_manager.transform_matrix.dump_css(f_css.fs);
        //        all_manager.vertical_align  .dump_css(f_css.fs);
        //        all_manager.letter_space    .dump_css(f_css.fs);
        //        all_manager.stroke_color    .dump_css(f_css.fs);
        //        all_manager.word_space      .dump_css(f_css.fs);
        //        all_manager.whitespace      .dump_css(f_css.fs);
        //        all_manager.fill_color      .dump_css(f_css.fs);
        //        all_manager.font_size       .dump_css(f_css.fs);
        //        all_manager.bottom          .dump_css(f_css.fs);
        //        all_manager.height          .dump_css(f_css.fs);
        //        all_manager.width           .dump_css(f_css.fs);
        //        all_manager.left            .dump_css(f_css.fs);
        //        all_manager.bgimage_size    .dump_css(f_css.fs);
        //
        //        // print css
        //        if(param.printing)
        //        {
        //            double ps = print_scale();
        //            f_css.fs << CSS::PRINT_ONLY << "{" << endl;
        //            all_manager.transform_matrix.dump_print_css(f_css.fs, ps);
        //            all_manager.vertical_align  .dump_print_css(f_css.fs, ps);
        //            all_manager.letter_space    .dump_print_css(f_css.fs, ps);
        //            all_manager.stroke_color    .dump_print_css(f_css.fs, ps);
        //            all_manager.word_space      .dump_print_css(f_css.fs, ps);
        //            all_manager.whitespace      .dump_print_css(f_css.fs, ps);
        //            all_manager.fill_color      .dump_print_css(f_css.fs, ps);
        //            all_manager.font_size       .dump_print_css(f_css.fs, ps);
        //            all_manager.bottom          .dump_print_css(f_css.fs, ps);
        //            all_manager.height          .dump_print_css(f_css.fs, ps);
        //            all_manager.width           .dump_print_css(f_css.fs, ps);
        //            all_manager.left            .dump_print_css(f_css.fs, ps);
        //            all_manager.bgimage_size    .dump_print_css(f_css.fs, ps);
        //            f_css.fs << "}" << endl;
        //        }
    }
    
    void HTMLRenderer::embed_file(ostream & out, const string & path, const string & type, bool copy)
    {
        string fn = get_filename(path);
        string suffix = (type == "") ? get_suffix(fn) : type;
        
        auto iter = EMBED_STRING_MAP.find(suffix);
        if(iter == EMBED_STRING_MAP.end())
        {
            cerr << "Warning: unknown suffix: " << suffix << endl;
            return;
        }
        
        const auto & entry = iter->second;
        
        if(param.*(entry.embed_flag))
        {
            ifstream fin(path, ifstream::binary);
            if(!fin)
                throw string("Cannot open file ") + path + " for embedding";
            out << entry.prefix_embed;
            
            if(entry.base64_encode)
            {
                out << Base64Stream(fin);
            }
            else
            {
                out << endl << fin.rdbuf();
            }
            out.clear(); // out will set fail big if fin is empty
            out << entry.suffix_embed << endl;
        }
        else
        {
            out << entry.prefix_external;
            writeAttribute(out, fn);
            out << entry.suffix_external << endl;
            
            if(copy)
            {
                ifstream fin(path, ifstream::binary);
                if(!fin)
                    throw string("Cannot copy file: ") + path;
                auto out_path = param.dest_dir + "/" + fn;
                ofstream out(out_path, ofstream::binary);
                if(!out)
                    throw string("Cannot open file ") + path + " for embedding";
                out << fin.rdbuf();
                out.clear(); // out will set fail big if fin is empty
            }
        }
    }
    
    const std::string HTMLRenderer::MANIFEST_FILENAME = "manifest";
    
    
}// namespace pdf2htmlEX
