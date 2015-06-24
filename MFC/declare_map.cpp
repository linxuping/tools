#include <stdio.h>

#define AFX_NOVTABLE //__declspec(novtable)
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef unsigned int UINT_PTR, *PUINT_PTR;
//#define PASCAL      __stdcall  ???
#define PASCAL  
#define AFX_MSG_CALL


class CCmdTarget;
typedef void (AFX_MSG_CALL CCmdTarget::*AFX_PMSG)(void);
struct AFX_MSGMAP_ENTRY
{
	UINT nMessage;   // windows message
	UINT nCode;      // control code or WM_NOTIFY code
	UINT nID;        // control ID (or 0 for windows messages)
	UINT nLastID;    // used for entries specifying a range of control id's
	UINT_PTR nSig;       // signature type (action) or pointer to message #
	AFX_PMSG pfn;    // routine to call (or special value)
};
struct AFX_MSGMAP
{
	const AFX_MSGMAP* (PASCAL* pfnGetBaseMap)();
	const AFX_MSGMAP_ENTRY* lpEntries;
};

#define DECLARE_MESSAGE_MAP() \
public: \
	static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
	virtual const AFX_MSGMAP* GetMessageMap() const; \

//#define BEGIN_MESSAGE_MAP(theClass, baseClass)  ???
//	PTM_WARNING_DISABLE ???
#define BEGIN_MESSAGE_MAP(theClass, baseClass) \
	const AFX_MSGMAP* theClass::GetMessageMap() const \
		{ return GetThisMessageMap(); } \
	const AFX_MSGMAP* PASCAL theClass::GetThisMessageMap() \
	{ \
		typedef theClass ThisClass;						   \
		typedef baseClass TheBaseClass;					   \
		static const AFX_MSGMAP_ENTRY _messageEntries[] =  \
		{

#define END_MESSAGE_MAP() \
		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 } \
	}; \
		static const AFX_MSGMAP messageMap = \
		{ &TheBaseClass::GetThisMessageMap, &_messageEntries[0] }; \
		return &messageMap; \
	}								  
//	PTM_WARNING_RESTORE ???

#define WM_COMMAND                      0x0111
#define CN_COMMAND              0               // void ()
#define ID_HELP                         0xE146      // first attempt for F1  =57670
typedef unsigned short      WORD;
enum AfxSig
{
	AfxSig_end = 0,     // [marks end of message map]
	AfxSigCmd_v,				// void ()
};

#define ON_COMMAND(id, memberFxn) \
	{ WM_COMMAND, CN_COMMAND, (WORD)id, (WORD)id, AfxSigCmd_v, \
		static_cast<AFX_PMSG> (memberFxn) },
		// ON_COMMAND(id, OnBar) is the same as
		//   ON_CONTROL(0, id, OnBar) or ON_BN_CLICKED(0, id, OnBar)
#define ON_COMMAND_END() \
	{ 0, 0, (WORD)10, (WORD)0, AfxSig_end, 0 },

class AFX_NOVTABLE CCmdTarget{
	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CCmdTarget, CCmdTarget)
	ON_COMMAND_END()
END_MESSAGE_MAP()


class base: public CCmdTarget{
};
class derived: public base{
	DECLARE_MESSAGE_MAP()
};
class myapp: public CCmdTarget{
	DECLARE_MESSAGE_MAP()
public:
	void OnHelp(){}
};

BEGIN_MESSAGE_MAP(derived, base)
	ON_COMMAND(ID_HELP, &myapp::OnHelp)
END_MESSAGE_MAP()

//dissect.
int main()
{
	derived* pd = new derived();
	const AFX_MSGMAP* pmap = pd->GetMessageMap();
	const AFX_MSGMAP_ENTRY* pentry = pmap->lpEntries;
	printf("pmap:%p \n",pmap);
	printf("pentry:%p %u \n",pentry, pentry[0].nID);
	printf("pentry:%p %u \n",pentry, pentry[1].nID);
	delete pd;
	return 0;
}


