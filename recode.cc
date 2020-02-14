 HKPosition p = fz_subbuf_search_second(text_select->string,new_key,start);
    int position = p.position;
    int spaceCount = p.spaceCount;
    while (position  > 0){
        HKSelect select = {0};
        swf_push_rects_to_select(ctx,text_select,p.position/size,keyLen/size+spaceCount,&select,size);
        hk_text_begin_end_select(ctx,page,p.position/size,keyLen/size+spaceCount,&begin,&end);
        hk_push_text_to_select(ctx,text_select->string,begin,end,&select,size);
        printf("display:\n");
        displayKey(select.string, 0, select.string->len);
        hk_push_select_to_search(ctx,&select,search);
        
        start = p.position + keyLen + spaceCount*size;
        p = fz_subbuf_search_second(text_select->string,new_key,start);
        position = p.position;
        spaceCount = p.spaceCount;
    }
    
HKPosition fz_subbuf_search_second(fz_buffer* buffer,fz_buffer* key,int start)
{
    int totalLen = buffer->len;
    int keyLen   = key->len;
    int spaceCount = 0;
    HKPosition p = {0};
    for (int i = start; i < totalLen;i++){
        int j = 0;
        spaceCount = 0;
        for (j; j < keyLen; j++){
            unsigned short unicode = 0;
            bool doub = (i+j+spaceCount*2)%2;
            if (!doub && (i+j+spaceCount*2) < (totalLen -1))
            {

                unicode = (buffer->data[i+j+1+spaceCount*2]<<8) + buffer->data[i+j+spaceCount*2];
//                getUTF8(unicode);printf(" %d\n",unicode);
            }
            if (unicode != 32)
            {
                if (buffer->data[i+j+spaceCount*2] != key->data[j]){
                break;
                }
            }
            else
            {
                j--;
                if (j<0) {
                    break;
                }
                else
                {
                    spaceCount++;
                }
            }
        }
        if (j == keyLen){
            p.position = i;
            p.spaceCount = spaceCount;
            return p;
        }
    }
    p.position = -1;
    p.spaceCount = 0;
    return p;
}
