#ifndef __OBJECT_HH__
#define __OBJECT_HH__
class STPusherObject
{
	public:
		STPusherObject(void *r,void* p);
		virtual ~STPusherObject();
		void *getRoot(){return fRoot;}
		void *getParent(){return fParent;}
	private:
		void *fRoot;
		void *fParent;
};


#endif
