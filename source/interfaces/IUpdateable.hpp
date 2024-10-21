#ifndef IUPDATEABLE
#define IUPDATEABLE

class IUpdateable
{
public:
	IUpdateable() = default;
	virtual ~IUpdateable() = default;

	//void FirstUpdate();
	//void PreUpdate();
	virtual void Update() = 0;
	//void PostUpdate();
	//void LastUpadte();
};

#endif
