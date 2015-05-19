#ifndef __ADPROCEDURE_H_
#define __ADPROCEDURE_H_

//-----------------------------------------------------------------------------
class AdProcedure {
public:
	virtual void Init(void);
	virtual void Quit(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	AdProcedure(void);
	virtual ~AdProcedure(void);
};

#endif
