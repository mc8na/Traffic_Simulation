#include <iostream>
#include "Animator.h"
#include "VehicleBase.h"
#include "Clock.h"
#include <fstream>

int main(int argc, char* argv[])
{
    std::ifstream inputFile;

    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " You need to include an input file with intersection specifications." << std::endl;
        exit(0);
    }
    
    inputFile.open(argv[1]);
    if (!inputFile.is_open()) 
    {
        std::cerr << "Error: Unable to open specified input file." << std::endl;
        exit(1);
    }

    //Animator::MAX_VEHICLE_COUNT = 9999;  // vehicles will be displayed with four digits
    //Animator::MAX_VEHICLE_COUNT = 999;  // vehicles will be displayed with three digits
    Animator::MAX_VEHICLE_COUNT = 99;  // vehicles will be displayed with two digits



    int maxTime;
    int halfSize;  // number of sections before intersection
    int ns_green;
    int ns_yellow;
    int ew_green;
    int ew_yellow;
    double prob_nsVehicle;
    double prob_ewVehicle;
    double prop_cars;
    double prop_SUVs;
    double probRight_cars;
    double probRight_SUVs;
    double probRight_trucks;
    double probLeft_cars;
    double probLeft_SUVs;
    double probLeft_trucks;

    inputFile >> maxTime >> halfSize >> ns_green >> ns_yellow >> ew_green >> ew_yellow;
    inputFile >> prob_nsVehicle >> prob_ewVehicle >> prop_cars >> prop_SUVs >> probRight_cars;
    inputFile >> probLeft_cars >> probRight_SUVs >> probLeft_SUVs >> probRight_trucks >> probLeft_trucks;

    inputFile.close();

    Animator anim(halfSize);

    // construct vectors of VehicleBase* of appropriate size, init to nullptr
    std::vector<VehicleBase*> westbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> eastbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> southbound(halfSize * 2 + 2, nullptr);
    std::vector<VehicleBase*> northbound(halfSize * 2 + 2, nullptr);

    char dummy;

    // test drawing vehicles moving eastbound and westbound
    Clock clock(halfSize, ns_green, ns_yellow, ew_green, ew_yellow, prob_nsVehicle, prob_ewVehicle, 
        prop_cars, prop_SUVs, probRight_cars, probRight_SUVs, probRight_trucks);

    for (int i = 0; i < maxTime; i++)
    {
        std::vector<Section*> sections = clock.Tick();
        std::vector<Section*>::iterator it = sections.begin();
        //std::vector<VehicleBase> vehicles;
        while(it != sections.end())
        {   
            //vehicles.emplace_back((*(*(*it)).getVehicle()).getVehicleType());
            switch ( (*(*it)).getLane() )
            {
                case Lane::NORTH:
                    northbound[(*(*it)).getIndex()] = (*(*it)).getVehicle();
                break;
                case Lane::SOUTH:
                    southbound[(*(*it)).getIndex()] = (*(*it)).getVehicle();
                break;
                case Lane::WEST:
                    westbound[(*(*it)).getIndex()] = (*(*it)).getVehicle();
                break;
                case Lane::EAST:
                    eastbound[(*(*it)).getIndex()] = (*(*it)).getVehicle();
                break;
            }
            it++;
        }

        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

        anim.draw(i);
        std::cin.get(dummy);

        eastbound.assign(halfSize * 2 + 2, nullptr); // reset
        westbound.assign(halfSize * 2 + 2, nullptr); // reset
        northbound.assign(halfSize * 2 + 2, nullptr);
        southbound.assign(halfSize * 2 + 2, nullptr);
    }
/*    
    VehicleBase vb1(VehicleBase::CAR);
    VehicleBase vb2(VehicleBase::SUV);
    VehicleBase vb3(VehicleBase::TRUCK);
    VehicleBase vb4(VehicleBase::CAR);
    VehicleBase vb5(VehicleBase::SUV);
    VehicleBase vb6(VehicleBase::TRUCK);

    for (int i = 0; i < 5; i++)
    {
        eastbound[12+i] = eastbound[13+i] = &vb1;
        eastbound[6+i] = eastbound[7+i] = eastbound[8+i] = &vb2;
        eastbound[0+i] = eastbound[1+i] = eastbound[2+i] = eastbound[3+i] = &vb3;

        westbound[12+i] = westbound[13+i] = &vb4;
        westbound[6+i] = westbound[7+i] = westbound[8+i] = &vb5;
        westbound[0+i] = westbound[1+i] = westbound[2+i] = westbound[3+i] = &vb6;

        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

        anim.draw(i);
        std::cin.get(dummy);

        eastbound.assign(halfSize * 2 + 2, nullptr); // reset
        westbound.assign(halfSize * 2 + 2, nullptr); // reset
    }

    // test drawing vehicles moving southbound and northbound
    VehicleBase vb7(VehicleBase::CAR);
    VehicleBase vb8(VehicleBase::SUV);
    VehicleBase vb9(VehicleBase::TRUCK);
    VehicleBase vb10(VehicleBase::CAR);
    VehicleBase vb11(VehicleBase::SUV);
    VehicleBase vb12(VehicleBase::TRUCK);

    for (int i = 0; i < 5; i++)
    {
        southbound[12+i] = southbound[13+i] = &vb7;
        southbound[6+i] = southbound[7+i] = southbound[8+i] = &vb8;
        southbound[0+i] = southbound[1+i] = southbound[2+i] = southbound[3+i] = &vb9;

        northbound[12+i] = northbound[13+i] = &vb10;
        northbound[6+i] = northbound[7+i] = northbound[8+i] = &vb11;
        northbound[0+i] = northbound[1+i] = northbound[2+i] = northbound[3+i] = &vb12;

        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);

        anim.draw(i + 10);
        std::cin.get(dummy);

        northbound.assign(halfSize * 2 + 2, nullptr); // reset
        southbound.assign(halfSize * 2 + 2, nullptr); // reset
    }
*/
}
