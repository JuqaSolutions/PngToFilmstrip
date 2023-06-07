#pragma once

#include <catch2/catch_all.hpp>
#include "../Sources/MainComponent.h"

//std::cout<<mainComponent.getNumChildComponents()<<std::endl;

//TODO Finish tests
//-----------------------
//For tests:
//----------
//        assert labelPath == filePath
//        WHEN user click on inputBowserButton THEN a path browser appear
//        WHEN user select a path on input browser THEN the path is shown in the inputTextEditor
//
//        WHEN user click on outputBowserButton THEN a path browser appear
//        WHEN user select a path on input browser THEN the path is shown in the outputTextEditor
//
//        WHEN user click on proceed button THEN
//          IF the input file folder is empty THEN an alert windows appear
//          IF the files in the input folder aren't .png type THEN an alert windows appear
//          IF the files in the input folder aren't same dimensions THEN an alert windows appear
//          IF the files in the input folder aren't Bitmap type THEN an alert windows appear
//          IF everything ok with above THEN a file is created in the output folder with the dimensions: width + nbr of files x height
//
//        WHEN user click on logoOpenWebBrowser THEN a link is open with a string "https://juqa.solutions"
//        WHEN user click on supportUsButton THEN a link is open with a string "https://patreon.com/........"

TEST_CASE("Get Application name", "[start]")
{
    MainComponent mainComponent;
    REQUIRE(mainComponent.getName() == "Png To Filmstrip");
}

TEST_CASE("Label text path is same than file path on launch", "[path]")
{
    MainComponent mainComponent;
    REQUIRE(mainComponent.getInputTextEditor().getText() == mainComponent.getFileToLoad().getFullPathName());
    REQUIRE(mainComponent.getOutputTextEditor().getText() == mainComponent.getFileToSave().getFullPathName());
}



