#include "application.h"

class PowerSupply {
  public:
    void setup() {
      setBrowoutResetLevel();
    }

    static const uint8_t desiredBOR = OB_BOR_LEVEL3;

    void setBrowoutResetLevel() {
      if(FLASH_OB_GetBOR() != desiredBOR) {
        /* Steps from http://www.st.com/web/en/resource/technical/document/programming_manual/CD00233952.pdf */
        FLASH_OB_Unlock();
        FLASH_WaitForLastOperation();
        FLASH_OB_BORConfig(desiredBOR);
        FLASH_OB_Launch();
        FLASH_OB_Lock();
      }
    }
};
