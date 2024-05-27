#ifndef IUPDATEABLE
#define IUPDATEABLE

__interface IUpdateable
{
	void PreUpdate();
	void Update();
	void PostUpdate();
};

#endif
