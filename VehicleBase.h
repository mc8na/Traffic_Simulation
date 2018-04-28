#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__

class VehicleBase
{
   public:
      static int vehicleCount;
      enum VehicleType {CAR, SUV, TRUCK};

   private:
      int         vehicleID;
      VehicleType vehicleType;

   public:
      VehicleBase(const VehicleBase& veh);
      VehicleBase(VehicleBase::VehicleType type);
      ~VehicleBase();

      inline int getVehicleID() { return this->vehicleID; }

      inline VehicleBase::VehicleType getVehicleType() const { return this->vehicleType; }
};

#endif
