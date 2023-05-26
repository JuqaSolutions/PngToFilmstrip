#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    //addAndMakeVisible(brandLabel);
    addAndMakeVisible(logoOpenWebBrowser);
    addAndMakeVisible(appNameLanel);

    addAndMakeVisible(inputFilesLabel);
    addAndMakeVisible(inputTextEditor);
    addAndMakeVisible(inputBrowserButton);

    addAndMakeVisible(outputFolderLabel);
    addAndMakeVisible(outputTextEditor);
    addAndMakeVisible(outputBrowserButton);

    addAndMakeVisible(supportUsButton);
    addAndMakeVisible(proceedButton);

    brandLabel.setText("Juqa.Solutions", juce::dontSendNotification);
    appNameLanel.setText("PNG TO FILMSTRIP", juce::dontSendNotification);
    inputFilesLabel.setText("Select the folder containing the .png files:", juce::dontSendNotification);
    inputTextEditor.setText(fileToLoad.getFullPathName(), juce::dontSendNotification);
    outputFolderLabel.setText("Select the output folder:", juce::dontSendNotification);
    outputTextEditor.setText(fileToSave.getFullPathName(), juce::dontSendNotification);
    supportUsButton.setButtonText("Support us!");
    proceedButton.setButtonText("Let's convert to filmstrip!");
    supportUsButton.setColour(juce::TextButton::buttonColourId, backgroundColour);

    inputBrowserButton.onClick = [&] {launchBrowser("Select the folder containing the .png files:", inputTextEditor, fileToLoad); };
    outputBrowserButton.onClick = [&] {launchBrowser("Select the output folder:", outputTextEditor, fileToSave); };
    //TODO Put real patreon link
    supportUsButton.onClick = []{juce::URL("https://patreon.com").launchInDefaultBrowser();};
    proceedButton.onClick = [this] {createFilmstripThread.launchThread();};
    logoOpenWebBrowser.onClick = []{juce::URL("https://juqa.solutions").launchInDefaultBrowser();};

    initializeImageButtons();
}

MainComponent::~MainComponent()
{
    if(createFilmstripThread.isThreadRunning())
        createFilmstripThread.stopThread(10);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (backgroundColour);

    auto bounds = getLocalBounds();
    auto height = bounds.getHeight() / 4;
    bounds.removeFromTop(height);
    auto inputBounds = bounds.removeFromTop(height);
    auto outputBounds = bounds.removeFromTop(height);

    g.setColour(browserBackgroundColour);
    g.fillRoundedRectangle(inputBounds.removeFromBottom(height / 2).toFloat(), 20);
    g.fillRoundedRectangle(outputBounds.removeFromBottom(height / 2).toFloat(), 20);

}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    auto height = bounds.getHeight() / 4;

    auto headerBounds = bounds.removeFromTop(height);
    auto inputBounds = bounds.removeFromTop(height);
    auto outputBounds = bounds.removeFromTop(height);
    auto footerBounds = bounds.removeFromTop(height);

    appNameLanel.setBounds(headerBounds.removeFromRight(headerBounds.getWidth() / 2));
    brandLabel.setBounds(headerBounds);
    logoOpenWebBrowser.setBounds(headerBounds);

    inputFilesLabel.setBounds(inputBounds.removeFromTop(inputBounds.getHeight() / 2));
    inputTextEditor.setBounds(inputBounds.removeFromLeft(inputBounds.getWidth() * 0.9f));
    inputBrowserButton.setBounds(inputBounds);

    outputFolderLabel.setBounds(outputBounds.removeFromTop(outputBounds.getHeight() / 2));
    outputTextEditor.setBounds(outputBounds.removeFromLeft(outputBounds.getWidth() * 0.9f));
    outputBrowserButton.setBounds(outputBounds);

    supportUsButton.setBounds(footerBounds.removeFromLeft(footerBounds.getWidth() / 2).reduced(height * 0.3f));
    proceedButton.setBounds(footerBounds.reduced(height * 0.3f));
}

void MainComponent::launchBrowser(juce::String browserText, juce::Label& textEditor, juce::File& fileToCopy)
{
    myChooser = std::make_unique<juce::FileChooser>(browserText, fileToCopy);

    myChooser->launchAsync(
            juce::FileBrowserComponent::openMode |
            juce::FileBrowserComponent::canSelectDirectories |
                    juce::FileBrowserComponent::saveMode |
                    juce::FileBrowserComponent::canSelectFiles |
                    juce::FileBrowserComponent::warnAboutOverwriting |
                    juce::FileBrowserComponent::useTreeView |
                    juce::FileBrowserComponent::doNotClearFileNameOnRootChange,
            [&](const juce::FileChooser& chooser)
            {
                juce::File returnedFile(chooser.getResult());
                if (returnedFile.getFileName().length() != 0)
                {
                    textEditor.setText(returnedFile.getFullPathName(), juce::dontSendNotification);
                    fileToCopy = returnedFile;
                }
            });
}

void MainComponent::proceed()
{

    /**
     *  use 2 methods for launch the browser
        input folder need to be a folder not a file + containing .png files ( need to test) and perhaps at least 2 files minimum?
        output folder need to be a file not a folder + with an extension .png type
        if the output file is already existing, nothing is written(keep the old file) <- Resolve this bug
     */

    DBG("Proceed() is loaded: " << fileToLoad.getFullPathName());

    if (!fileToLoad.exists()) {
        fileToLoad.createDirectory();
    }

    if (!fileToSave.exists()) {
        fileToSave.create();
    }

    if (fileToLoad.isDirectory()) {
        DBG("is directory");

        auto result = juce::Array<juce::File>();

        if (fileToLoad.findChildFiles(
                result,
                2,
                false,
                "*.png")) {
            DBG("contains of the directory: " << result.size());
            std::cout<<result.size()<<std::endl;

            juce::PNGImageFormat imageFileFormat;
            juce::Array<juce::Image> imageArray{};
            int width = -1;
            int height = -1;
            int outputHeight = 0;

            for (juce::File file: result)
            {
                juce::Image tempImage;
                int tempWidth{0};
                int tempHeight{0};

                tempImage = juce::ImageFileFormat::loadFrom(file);

                std::cout<<tempImage.isValid()<<std::endl;
                if (!tempImage.isValid())
                {
                    juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon, "File not valid", "It seems that at least one file isn't valid.");
                    return;
                }
                tempWidth = tempImage.getWidth();
                tempHeight = tempImage.getHeight();

                if (width ==-1)
                {
                    width = tempWidth;
                    height = tempHeight;
                }
                else
                {
                    if (tempWidth != width || tempHeight != height)
                    {
                        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon, "Wrong dimensions", "All the .png files must have the same dimensions");
                        return;
                    }
                }

                imageArray.add(tempImage);
//                width = tempWidth;
//                height = tempHeight;
            }

            outputHeight = height * imageArray.size();

            juce::Image outputImage{juce::Image::ARGB, width, outputHeight, true};

            int arrayIndex = 0;
            int heightForLoop = 0;

            while (arrayIndex < imageArray.size()) {
                for (int h = 0; h < height; ++h) {
                    for (int w = 0; w < width; ++w) {
                        outputImage.setPixelAt(w, heightForLoop, imageArray.getReference(arrayIndex).getPixelAt(w, h));
                    }
                    ++heightForLoop;
                }
                ++arrayIndex;
            }

            juce::FileOutputStream outputStream{fileToSave};
            imageFileFormat.writeImageToStream(outputImage, outputStream);
        }
        else
        {
            juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon, "Empty folder", "The folder containing the .png files is empty. Or your files aren't .png type");
        }
    }
}

void MainComponent::initializeImageButtons()
{
    juce::Image logo = juce::ImageCache::getFromMemory(BinaryData::juqa_logo_png, BinaryData::juqa_logo_pngSize);
    logoOpenWebBrowser.setImages(false,
                                 true,
                                 true,
                                 logo,
                                 1.0f,
                                 juce::Colours::transparentBlack,
                                 logo,
                                 1.0f,
                                 juce::Colours::transparentBlack,
                                 logo,
                                 1.0f,
                                 juce::Colours::transparentBlack
                                 );
}
