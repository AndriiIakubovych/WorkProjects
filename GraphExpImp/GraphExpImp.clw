; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGraphExpImpView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GraphExpImp.h"
LastPage=0

ClassCount=26
Class1=CGraphExpImpApp
Class2=CGraphExpImpDoc
Class3=CGraphExpImpView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME (English (U.S.))
Class5=AddProfileDlg
Class6=ProfilesExpImpRead
Class7=FilesExpImpRead
Resource3=IDR_ACCELERATOR
Class8=AddFilesExpDlg
Class9=AddFilesImpDlg
Class10=EditFilesExpDlg
Class11=EditFilesImpDlg
Class12=EditProfileExpDlg
Class13=EditProfileImpDlg
Class14=EditProfileReorgDlg
Class15=EditProfileTransDlg
Class16=NregionRead
Class17=DesspaceRead
Class18=TplineRead
Class19=TpnameRead
Class20=TplevRead
Class21=AddSampleProfileDlg
Class22=AboutProgramDlg
Class23=PlsizeRead
Class24=ItemMenuRead
Class25=AdvToolBar
Class26=NameNewTableDlg
Resource4=IDR_TOOLBAR (Russian)
Resource5=IDR_TOOLBAR

[CLS:CGraphExpImpApp]
Type=0
HeaderFile=GraphExpImp.h
ImplementationFile=GraphExpImp.cpp
Filter=N

[CLS:CGraphExpImpDoc]
Type=0
HeaderFile=GraphExpImpDoc.h
ImplementationFile=GraphExpImpDoc.cpp
Filter=N

[CLS:CGraphExpImpView]
Type=0
HeaderFile=GraphExpImpView.h
ImplementationFile=GraphExpImpView.cpp
Filter=W
BaseClass=CView
VirtualFilter=VWC
LastObject=CGraphExpImpView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_APP_EXIT




[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:ProfilesExpImpRead]
Type=0
HeaderFile=ProfilesExpImpRead.h
ImplementationFile=ProfilesExpImpRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:ProfilesExpImpRead]
DB=1
DBType=ODBC
ColumnCount=17
Column1=[Id], 4, 4
Column2=[Name_profile], 12, 510
Column3=[Number_section], 4, 4
Column4=[Group_section], 4, 4
Column5=[Path_section], 12, 510
Column6=[Type_source_data], 4, 4
Column7=[Folder], 12, 510
Column8=[Factor_x], 8, 8
Column9=[Factor_y], 8, 8
Column10=[Shift_x], 8, 8
Column11=[Shift_y], 8, 8
Column12=[Turn], 8, 8
Column13=[Initial_order_coordinates], 4, 4
Column14=[Graph_area], -7, 1
Column15=[Graph_area_id], 4, 4
Column16=[Unit], 4, 4
Column17=[Exp_imp], 12, 510

[CLS:FilesExpImpRead]
Type=0
HeaderFile=FilesExpImpRead.h
ImplementationFile=FilesExpImpRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=FilesExpImpRead

[DB:FilesExpImpRead]
DB=1
DBType=ODBC
ColumnCount=22
Column1=[File_id], 4, 4
Column2=[Id], 4, 4
Column3=[File_name], 12, 510
Column4=[Type_graph_object], 4, 4
Column5=[Type_graph_obj], 4, 4
Column6=[Complement_areas_centers_knots], -7, 1
Column7=[Type_broken], 4, 4
Column8=[Level_lines], 4, 4
Column9=[Break_broken_segments], -7, 1
Column10=[Skip_superfluous_points], -7, 1
Column11=[Accepting_type_text], 4, 4
Column12=[Level_text], 4, 4
Column13=[Code_text], 4, 4
Column14=[Transform_denotations], 4, 4
Column15=[Type_transformed_broken], 4, 4
Column16=[Level_primitives], 4, 4
Column17=[Size_denotations], 8, 8
Column18=[Import_descriptions], -7, 1
Column19=[Number_field_description], 4, 4
Column20=[Accepting_type_description], 4, 4
Column21=[Level_descriptions], 4, 4
Column22=[Height_inscriptions_descriptions], 8, 8

[DLG:]
Type=1
Class=AddProfileDlg
ControlCount=33
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC12,static,1342308352
Control4=IDC_EDIT2,edit,1484849280
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_STATIC11,static,1342308352
Control7=IDC_COMBO1,combobox,1344339971
Control8=IDC_STATIC13,button,1342177287
Control9=IDC_STATIC1,static,1342308352
Control10=IDC_EDIT3,edit,1350631552
Control11=IDC_STATIC2,static,1342308352
Control12=IDC_EDIT4,edit,1350631552
Control13=IDC_STATIC3,static,1342308352
Control14=IDC_EDIT5,edit,1350631552
Control15=IDC_STATIC4,static,1342308352
Control16=IDC_EDIT6,edit,1350631552
Control17=IDC_STATIC5,static,1342308352
Control18=IDC_EDIT7,edit,1350631552
Control19=IDC_RADIO3,button,1476526089
Control20=IDC_RADIO4,button,1476395017
Control21=IDC_STATIC9,static,1476526080
Control22=IDC_COMBO2,combobox,1478557699
Control23=IDC_SELECT_NAME_PROFILE,static,1342308352
Control24=IDC_EDIT1,edit,1350631552
Control25=IDC_STATIC6,button,1476395015
Control26=IDC_STATIC8,button,1342177287
Control27=IDC_STATIC10,button,1342177287
Control28=IDC_RADIO5,button,1342308361
Control29=IDC_RADIO6,button,1342177289
Control30=IDC_CHARACTERISTICS_PROFILE,button,1342177287
Control31=IDC_CHECK1,button,1476460547
Control32=IDC_SELECT_TYPE_PROFILE,static,1342308352
Control33=IDC_TYPE_PROFILE,combobox,1344339971

[CLS:AddProfileDlg]
Type=0
HeaderFile=AddProfileDlg.h
ImplementationFile=AddProfileDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=AddProfileDlg
VirtualFilter=dWC

[CLS:AddFilesExpDlg]
Type=0
HeaderFile=AddFilesExpDlg.h
ImplementationFile=AddFilesExpDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_QUERY

[CLS:AddFilesImpDlg]
Type=0
HeaderFile=AddFilesImpDlg.h
ImplementationFile=AddFilesImpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_OPERATIONS_CREATE_PROFILE
VirtualFilter=dWC

[CLS:EditFilesExpDlg]
Type=0
HeaderFile=EditFilesExpDlg.h
ImplementationFile=EditFilesExpDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:EditFilesImpDlg]
Type=0
HeaderFile=EditFilesImpDlg.h
ImplementationFile=EditFilesImpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TYPE_TEXT
VirtualFilter=dWC

[CLS:EditProfileExpDlg]
Type=0
HeaderFile=EditProfileExpDlg.h
ImplementationFile=EditProfileExpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SECTION
VirtualFilter=dWC

[CLS:EditProfileImpDlg]
Type=0
HeaderFile=EditProfileImpDlg.h
ImplementationFile=EditProfileImpDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_USUAL

[CLS:EditProfileReorgDlg]
Type=0
HeaderFile=EditProfileReorgDlg.h
ImplementationFile=EditProfileReorgDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_OPERATIONS_CREATE_SAMPLE
VirtualFilter=dWC

[CLS:EditProfileTransDlg]
Type=0
HeaderFile=EditProfileTransDlg.h
ImplementationFile=EditProfileTransDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SHIFT_Y2
VirtualFilter=dWC

[CLS:NregionRead]
Type=0
HeaderFile=NregionRead.h
ImplementationFile=NregionRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:NregionRead]
DB=1
DBType=ODBC
ColumnCount=6
Column1=[NUMREG], 5, 2
Column2=[GRUPREG], -6, 1
Column3=[NAMREG], 12, 100
Column4=[PATH], 12, 40
Column5=[TYPBASE], -6, 1
Column6=[PARENT], 5, 2

[CLS:DesspaceRead]
Type=0
HeaderFile=DesspaceRead.h
ImplementationFile=DesspaceRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:DesspaceRead]
DB=1
DBType=ODBC
ColumnCount=6
Column1=[PERSON], 5, 2
Column2=[NUMSPACE], 5, 2
Column3=[NAMESPACE], 12, 100
Column4=[TYPSPACE], -6, 1
Column5=[CRIT], -6, 1
Column6=[NUMPOINT], 5, 2

[DB:TplineRead]
DB=1
DBType=ODBC
ColumnCount=15
Column1=[VIDOBJ], -6, 1
Column2=[TYPBLINE], -6, 1
Column3=[USEORDER], -6, 1
Column4=[NAMTP], 12, 80
Column5=[TYPLINE], -6, 1
Column6=[ICOLBOUM], 4, 4
Column7=[WIDTH], -6, 1
Column8=[CLOSE], -6, 1
Column9=[TYPSYS], -6, 1
Column10=[ICOLOUR], 4, 4
Column11=[ICOLDASH], 4, 4
Column12=[STYLDASH], -6, 1
Column13=[MODEADR], -6, 1
Column14=[SIZEVAL], 7, 4
Column15=[NUMFIG], 5, 2

[CLS:TplineRead]
Type=0
HeaderFile=TplineRead.h
ImplementationFile=TplineRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[CLS:TpnameRead]
Type=0
HeaderFile=TpnameRead.h
ImplementationFile=TpnameRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=TpnameRead

[DB:TpnameRead]
DB=1
DBType=ODBC
ColumnCount=10
Column1=[VIDOBJ], -6, 1
Column2=[TYPNAM], -6, 1
Column3=[USEORDER], -6, 1
Column4=[NAMNAM], 12, 80
Column5=[ICOLTEXT], 4, 4
Column6=[NUMFONT], -6, 1
Column7=[TYPSYS], -6, 1
Column8=[NUMEXPR], -6, 1
Column9=[STYLENAME], -6, 1
Column10=[NUMTPNAM], -6, 1

[CLS:TplevRead]
Type=0
HeaderFile=TplevRead.h
ImplementationFile=TplevRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:TplevRead]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[vidobj], -6, 1
Column2=[type], 5, 2
Column3=[USEORDER], -6, 1
Column4=[dlevel], 5, 2

[CLS:AddSampleProfileDlg]
Type=0
HeaderFile=AddSampleProfileDlg.h
ImplementationFile=AddSampleProfileDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AddSampleProfileDlg

[ACL:IDR_ACCELERATOR]
Type=1
Class=?
Command1=ID_OPERATIONS_CREATE_FILE
Command2=ID_OPERATIONS_CREATE_PROFILE
CommandCount=2

[CLS:AboutProgramDlg]
Type=0
HeaderFile=AboutProgramDlg.h
ImplementationFile=AboutProgramDlg.cpp
BaseClass=CDialog
Filter=D

[CLS:PlsizeRead]
Type=0
HeaderFile=PlsizeRead.h
ImplementationFile=PlsizeRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:PlsizeRead]
DB=1
DBType=ODBC
ColumnCount=41
Column1=[NUMREG], 5, 2
Column2=[PLANSHET], -6, 1
Column3=[SIZX], 7, 4
Column4=[SIZY], 7, 4
Column5=[MASKSQLEN], -6, 1
Column6=[MASH], 7, 4
Column7=[BSQX], 5, 2
Column8=[BSQY], 5, 2
Column9=[ESQX], 5, 2
Column10=[ESQY], 5, 2
Column11=[ABCD], 12, 8
Column12=[NUMSQT], -6, 1
Column13=[PLANCOVER], -6, 1
Column14=[NUMSQ], -6, 1
Column15=[LENNAMPL], -6, 1
Column16=[XMIN], 4, 4
Column17=[YMIN], 4, 4
Column18=[XMAX], 4, 4
Column19=[YMAX], 4, 4
Column20=[KX], 4, 4
Column21=[KY], 4, 4
Column22=[MODEADRBLD], -6, 1
Column23=[LEVADR], -6, 1
Column24=[DRAWADR], -6, 1
Column25=[TYPNAMSTR], -6, 1
Column26=[TYPNAMREG], -6, 1
Column27=[ADM], -7, 1
Column28=[ADMSTR], -7, 1
Column29=[AREA], -7, 1
Column30=[BUILDING], -7, 1
Column31=[UPBASE], -7, 1
Column32=[BUILDPASP], -7, 1
Column33=[ICON], -7, 1
Column34=[desline], -6, 1
Column35=[desicon], -6, 1
Column36=[raster], -6, 1
Column37=[Digitizer], -7, 1
Column38=[ISEXPIMP], -6, 1
Column39=[NumSqlBl], -6, 1
Column40=[NumSqlLine], -6, 1
Column41=[bal], -6, 1

[CLS:ItemMenuRead]
Type=0
HeaderFile=ItemMenuRead.h
ImplementationFile=ItemMenuRead.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:ItemMenuRead]
DB=1
DBType=ODBC
ColumnCount=9
Column1=[CODMENU], 5, 2
Column2=[CODITEM], 5, 2
Column3=[NUMITEM], 5, 2
Column4=[NAMEITEM], 12, 120
Column5=[CODCOMM], 5, 2
Column6=[CODICON], 5, 2
Column7=[HELPITEM], 12, 140
Column8=[ACCESS], -6, 1
Column9=[WRJOURN], -6, 1

[CLS:AdvToolBar]
Type=0
HeaderFile=AdvToolBar.h
ImplementationFile=AdvToolBar.cpp
BaseClass=CToolBarCtrl
Filter=W

[CLS:NameNewTableDlg]
Type=0
HeaderFile=NameNewTableDlg.h
ImplementationFile=NameNewTableDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NAME_TABLE
VirtualFilter=dWC

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=ID_CREATE_PROFILE
Command2=ID_CREATE_FILE
Command3=ID_CREATE_SAMPLE
Command4=ID_EDIT
Command5=ID_DELETE
Command6=ID_EXECUTE
Command7=ID_EXIT
Command8=ID_OPEN_HELP
Command9=ID_OPEN_ABOUT
CommandCount=9

[TB:IDR_TOOLBAR (Russian)]
Type=1
Class=?
Command1=ID_CREATE_PROFILE
Command2=ID_CREATE_FILE
Command3=ID_CREATE_SAMPLE
Command4=ID_EDIT
Command5=ID_DELETE
Command6=ID_EXECUTE
Command7=ID_EXIT
Command8=ID_OPEN_HELP
Command9=ID_OPEN_ABOUT
CommandCount=9

