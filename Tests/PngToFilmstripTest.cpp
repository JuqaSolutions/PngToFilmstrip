#pragma once

#include <catch2/catch_all.hpp>
#include "../Sources/MainComponent.h"


TEST_CASE("one is equal to one", "[dummy]")
{
//auto gui = juce::ScopedJuceInitialiser_GUI {};
MainComponent mainComponent;
std::cout<<mainComponent.getNumChildComponents()<<std::endl;
//REQUIRE(8 == mainComponent.returnAnInt());
}