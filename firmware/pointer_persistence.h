// Combine the persistence and pointer classes
#pragma once
#include "pointer.h"
#include "persistence.h"

class PointerPersistence : public PointerObserver {
  public:
    PointerPersistence(Pointer &pointer, Persistence &persistence)
      : pointer(pointer), persistence(persistence) {
    }

    void setup() {
      pointer.setInitialAngle(persistence.loadPosition());
      pointer.addObserver(this);
    }

    void angleChanged(int angle) {
      persistence.savePosition(angle);
    }

  private:
    Pointer &pointer;
    Persistence &persistence;
};
