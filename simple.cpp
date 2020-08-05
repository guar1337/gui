class TileFrame;

class TestMainFrame {

RQ_OBJECT("TestMainFrame")

private:
   TGMainFrame        *fMain;
   TGDockableFrame    *fMenuDock;
   TGCompositeFrame   *fStatusFrame;
   TGCanvas           *fCanvasWindow;
   TileFrame          *fContainer;
   TGTextEntry        *fTestText;
   TGButton           *fTestButton;
   TGColorSelect      *fColorSel;

   TGMenuBar          *fMenuBar;
   TGPopupMenu        *fMenuFile, *fMenuTest, *fMenuHelp;
   TGPopupMenu        *fCascadeMenu, *fCascade1Menu, *fCascade2Menu;
   TGPopupMenu        *fMenuNew1, *fMenuNew2;
   TGLayoutHints      *fMenuBarLayout, *fMenuBarItemLayout, *fMenuBarHelpLayout;

public:
   TestMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~TestMainFrame();

   // slots
   void CloseWindow();
   void DoButton();
   void HandleMenu(Int_t id);
   void HandlePopup() { printf("menu popped up\n"); }
   void HandlePopdown() { printf("menu popped down\n"); }

   void Created() { Emit("Created()"); } //*SIGNAL*
   void Welcome() { printf("TestMainFrame has been created. Welcome!\n"); }
};

void simple()
{


	const char *filetypes[] = { "All files",	  "*",
									 "ROOT files",	 "*.root",
									 "ROOT macros",	"*.C",
									 "Text files",	 "*.[tT][xX][tT]",
									 0,					0 };
	TGMainFrame        *fMain = new TGMainFrame(gClient->GetRoot(), 400, 220);
	TString dir(".");
	TGFileInfo fi;
	fi.fFileTypes = filetypes;
	fi.fIniDir	 = StrDup(dir);
	printf("fIniDir = %s\n", fi.fIniDir);
	new TGFileDialog(gClient->GetRoot(), fMain, kFDOpen, &fi);
	printf("Open file: %s (dir: %s)\n", fi.fFilename, fi.fIniDir);
	dir = fi.fIniDir;
}