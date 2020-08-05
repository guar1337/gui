#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <RQ_OBJECT.h>

class MyMainFrame {
	RQ_OBJECT("MyMainFrame")
private:
	TGMainFrame			*fMainFrame;
	TGCompositeFrame *fFileNameFrame;
	TRootEmbeddedCanvas *fEcanvas;
	TGLayoutHints	 *fFrameLayout, *fL5, *fL6;
	TGButton	*fGeoCheckButton1, *fGeoCheckButton2, *fGeoCheckButton3, *fGeoCheckButton4, *fSingleFileRadio, *fDirectoryRadio;
	TGTextEntry *fFileNameMessage;
	TGTextBuffer *fFileNameTextBuffer, *fWelcomeMessageTextBuffer;
	TGLabel	*fFileNameLabel;
	TGRadioButton *fRadioSingleOrDirectory;
public:
	MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
	virtual ~MyMainFrame();
	void DoDraw();
	void openTBrowser();
	void singleFile();
	void ProcessSingleOrDirectory();
};

MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h) {
	// Create a main frame
	fMainFrame = new TGMainFrame(p,w,h);
	fFrameLayout = new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX,	
									200, 2, 2, 2);
	fL5 = new TGLayoutHints(kLHintsLeft | kLHintsCenterY,
									3, 5, 0, 0);
	fL6 = new TGLayoutHints(kLHintsRight | kLHintsCenterY,
									0, 2, 0, 0);



	fFileNameFrame = new TGCompositeFrame(fMainFrame, 60, 20, kHorizontalFrame);
	fFileNameMessage	= new TGTextEntry(fFileNameFrame, fWelcomeMessageTextBuffer = new TGTextBuffer(100));
	fWelcomeMessageTextBuffer->AddText(0, "This is a test message box.");
	fFileNameLabel = new TGLabel(fFileNameFrame, new TGString("								Message:"));
	fFileNameFrame->AddFrame(fFileNameMessage, fL6);
	fFileNameFrame->AddFrame(fFileNameLabel, fL6);
	
	

	// Create canvas widget
	fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMainFrame,200,200);
	fMainFrame->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX |
						 kLHintsExpandY, 10,10,10,1));
	// Create a horizontal frame widget with buttons
	TGHorizontalFrame *hframe = new TGHorizontalFrame(fMainFrame,200,40);

	TGTextButton *draw = new TGTextButton(hframe,"&Draw");
	draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
	hframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,
														  5,5,3,4));

	TGTextButton *exit = new TGTextButton(hframe,"&Exit",
										  "gApplication->Terminate(0)");
	hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,
														  5,5,3,4));
	fMainFrame->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,
															2,2,2,2));


	fMainFrame->AddFrame(fGeoCheckButton1 = new TGCheckButton(fMainFrame, "Geometry 1", 71), fFrameLayout);
	fMainFrame->AddFrame(fGeoCheckButton2 = new TGCheckButton(fMainFrame, "Geometry 2", 72), fFrameLayout);
	fMainFrame->AddFrame(fGeoCheckButton3 = new TGCheckButton(fMainFrame, "Geometry 3", 73), fFrameLayout);
	fMainFrame->AddFrame(fGeoCheckButton4 = new TGCheckButton(fMainFrame, "Gas target", 74), fFrameLayout);
	fMainFrame->AddFrame(fSingleFileRadio = new TGRadioButton(fMainFrame, "Process single File", 81), fFrameLayout);
	fMainFrame->AddFrame(fDirectoryRadio = new TGRadioButton(fMainFrame, "Process whole directory", 82), fFrameLayout);
	fSingleFileRadio->Connect("Clicked()", "MyMainFrame", this, "ProcessSingleOrDirectory()");
	fDirectoryRadio->Connect("Clicked()", "MyMainFrame", this, "ProcessSingleOrDirectory()");
	fMainFrame->AddFrame(fFileNameLabel, fL5);
	fMainFrame->AddFrame(fFileNameFrame, fL5);
	// Set a name to the main frame
	fMainFrame->SetWindowName("Simple Example");

	// Map all subwindows of main frame
	fMainFrame->MapSubwindows();

	// Initialize the layout algorithm
	fMainFrame->Resize(fMainFrame->GetDefaultSize());

	// Map main frame
	fMainFrame->MapWindow();
}
void MyMainFrame::DoDraw() {
	// Draws function graphics in randomly chosen interval
	TF1 *f1 = new TF1("f1","sin(x)/x",0,gRandom->Rndm()*10);
	f1->SetLineWidth(3);
	f1->Draw();
	TCanvas *fCanvas = fEcanvas->GetCanvas();
	fCanvas->cd();
	fCanvas->Update();
}


void MyMainFrame::singleFile()
{
	const char *filetypes[] = { "All files",	  "*",
										 "ROOT files",	 "*.root",
										 "ROOT macros",	"*.C",
										 "Text files",	 "*.[tT][xX][tT]",
										 0,					0 };
	TString dir("home/zalewski/Desktop");
	TGFileInfo fi;
	fi.fFileTypes = filetypes;
	fi.fIniDir	 = StrDup(dir);
	printf("fIniDir = %s\n", fi.fIniDir);
	new TGFileDialog(gClient->GetRoot(), fMainFrame, kFDOpen, &fi);
	printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
	dir = fi.fIniDir;

	fFileNameMessage->SetText(dir.Data());
	fFileNameLabel->SetText("Process single file: ");
	gSystem->Exec("make");
}

void MyMainFrame::ProcessSingleOrDirectory()
{
	// Handle radio buttons.
	TGButton *btn = (TGButton *) gTQSender;
	Int_t id = btn->WidgetId();

	if (id == 81)
	{
		fDirectoryRadio->SetState(kButtonUp);
		fFileNameMessage->SetEnabled(1);
		singleFile();
		fGeoCheckButton1->SetEnabled(0);
		fGeoCheckButton2->SetEnabled(0);
		fGeoCheckButton3->SetEnabled(0);
		fGeoCheckButton4->SetEnabled(0);
	}

	else if (id==82)
	{
		fSingleFileRadio->SetState(kButtonUp);
		fFileNameMessage->SetEnabled(0);
		fGeoCheckButton1->SetEnabled(1);
		fGeoCheckButton2->SetEnabled(1);
		fGeoCheckButton3->SetEnabled(1);
		fGeoCheckButton4->SetEnabled(1);
	}
}

MyMainFrame::~MyMainFrame() {
	// Clean up used widgets: frames, buttons, layout hints
	fMainFrame->Cleanup();
	delete fMainFrame;
}
void interface() {
	// Popup the GUI...
	new MyMainFrame(gClient->GetRoot(),100,100);
}


