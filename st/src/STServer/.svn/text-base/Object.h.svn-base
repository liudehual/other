#ifndef __OBJECT_HH__
#define __OBJECT_HH__

#define VIDEO_TYPE 0x01
#define AUDIO_TYPE 0x02
class Object
{
	public:
		Object(void *r,void* p);
		virtual ~Object();
		void *getRoot(){return fRoot;}
		void *getParent(){return fParent;}
	private:
		void *fRoot;
		void *fParent;
};


#endif
