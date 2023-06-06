#pragma once

#include <catch2/catch_all.hpp>
#include "../Sources/MainComponent.h"

//std::cout<<mainComponent.getNumChildComponents()<<std::endl;


TEST_CASE("Get Application name", "[start]")
{
    MainComponent mainComponent;
    REQUIRE(mainComponent.getName() == "Png To Filmstrip");
}

