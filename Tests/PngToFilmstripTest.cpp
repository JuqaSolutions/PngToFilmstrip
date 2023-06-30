#pragma once
//Copyright 2023 Julien CAUBET
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

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



