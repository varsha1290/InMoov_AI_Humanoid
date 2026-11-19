#include "joint.h"
bool Joint::moveTo(float angle){
 if(!cfg_.enabled||!driver_||angle<cfg_.minAngleDeg||angle>cfg_.maxAngleDeg)return false;
 if(cfg_.reversed) angle=cfg_.minAngleDeg+cfg_.maxAngleDeg-angle;
 float span=cfg_.maxAngleDeg-cfg_.minAngleDeg;
 if(span<=0)return false;
 float t=(angle-cfg_.minAngleDeg)/span;
 uint16_t pulse=(uint16_t)(cfg_.minPulseUs+t*(cfg_.maxPulseUs-cfg_.minPulseUs));
 return driver_->writePulseUs(cfg_.channel,pulse);
}
