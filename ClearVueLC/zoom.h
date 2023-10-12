enum zoomCodes
  {
    zoomUp = 20,
    zoomDown
  };
enum catResources
  {
    catBoard = 1,
    catTest,
    catDisplay,
    catNetwork
  };
enum catIDs
  {
    boardId = 32,
    pRAMInitData,
    primaryInit,
    timeOutConst,
    vendorInfo,
    boardFlags
  };
  
enum VendorIDInfo
  {
    vendorId = 1,
    serialNum,
    revLevel,
    partNum
  };
/*
#define ParamBlockHeader \
	struct QElem *qLink; \
	short qType; \
	short ioTrap; \
	Ptr ioCmdAddr; \
	ProcPtr ioCompletion; \
	OSErr ioResult; \
	StringPtr ioNamePtr; \
	short ioVRefNum
*/
/* Driver control parameter block */
/*
typedef struct controlparam
{
  ParamBlockHeader;
  short ioRefNum;
  short csCode;
  long csParam;
} controlparam;
*/