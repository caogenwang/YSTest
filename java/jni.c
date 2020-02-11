{
			jclass accesserClass = (*env)->FindClass(env, PACKAGENAME "/MuPDFCore");;
			jmethodID setStringBufUnicode = (*env)->GetMethodID(env,accesserClass, "setStringBufUnicode", "([I)V");
			
			
			int bufLen = s->string->len;
			for (int j = 0; j < bufLen;j = j + sizeof(unsigned short)) {
				unsigned short unicode = (s->string->data[j+1]<<8) + s->string->data[j];
				LOGI("unicode:%d\n",unicode);
			}
			
			jintArray intarray;
			intarray = (*env)->NewIntArray(env,);
			(*env)->SetIntArrayRegion(env,intarray, 0, bufLen, (const jint*));
			(*env)->CallVoidMethod(env,thiz, setStringBufUnicode, intarray);
			(*env)->DeleteLocalRef(env,intarray);
		}