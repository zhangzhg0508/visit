// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <QvisPluginWindow.h>
#include <QButtonGroup>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
#include <QWidget>
#include <QRadioButton>
#include <QTreeWidget>
#include <QHeaderView>
#include <QListWidget>
#include <QTreeView>

#include <PluginManagerAttributes.h>
#include <FileOpenOptions.h>
#include <DBOptionsAttributes.h>
#include <DataNode.h>
#include <ViewerProxy.h>

#include <QvisDBOptionsDialog.h>
#include <QvisPluginManagerAttributesDataModel.h>

#include <cctype>
#include <string>
#include <vector>

using std::string;
using std::vector;

// ****************************************************************************
//  Method: QvisPluginWindow::QvisPluginWindow
//
//  Purpose: 
//    This is the constructor for the QvisPluginWindow class.
//
//  Arguments:
//    subj    : The PluginAttributes object that the window observes.
//    caption : The string that appears in the window decorations.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//    Jeremy Meredith, Fri Sep 28 13:52:35 PDT 2001
//    Removed default settings capabilities.
//
//    Jeremy Meredith, Wed Jan 23 15:35:39 EST 2008
//    We're observer two subjects now, so inherit from simpleobserver.
//
//    Brad Whitlock, Wed Apr  9 11:04:01 PDT 2008
//    QString for caption, shortName.
//
//    Brad Whitlock, Tue Feb  9 13:46:15 PST 2010
//    Initialize data model pointers.
//
// ****************************************************************************

QvisPluginWindow::QvisPluginWindow(const QString &caption, const QString &shortName,
                                   QvisNotepadArea *notepad) :
    QvisPostableWindowSimpleObserver(caption, shortName, notepad,
                               QvisPostableWindowSimpleObserver::ApplyButton)
{
    pluginAtts = NULL;
    fileOpenOptions = NULL;
    plotDataModel = NULL;
    operatorDataModel = NULL;
    activeTab = 0;
    pluginsInitialized = false;
}

// ****************************************************************************
//  Method: QvisPluginWindow::~QvisPluginWindow
//
//  Purpose: 
//    This is the destructor for the QvisPluginWindow class.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//    Jeremy Meredith, Wed Jan 23 15:36:03 EST 2008
//    Also observer fileOpenOptions for the database options.
//
//    Brad Whitlock, Wed Nov 19 14:11:32 PST 2008
//    Detach if the subjects are not NULL.
//
// ****************************************************************************

QvisPluginWindow::~QvisPluginWindow()
{
    if(pluginAtts != 0)
        pluginAtts->Detach(this);
    if(fileOpenOptions != 0)
        fileOpenOptions->Detach(this);
}


// ****************************************************************************
// Method: QvisPluginWindow::ConnectSubjects
//
// Purpose: 
//   This function connects subjects so that the window observes them.
//
// Programmer: Jeremy Meredith
// Creation:   January 23, 2008
//
// Modifications:
//   Brad Whitlock, Tue Feb  9 11:47:38 PST 2010
//   I added the data model objects.
//
// ****************************************************************************

void
QvisPluginWindow::ConnectSubjects(PluginManagerAttributes *p, FileOpenOptions *f)
{
    pluginAtts = p;
    pluginAtts->Attach(this);

    fileOpenOptions = f;
    fileOpenOptions->Attach(this);

    // Create data models that will present data from the plugin atts to the
    // views that show it in this window.
    plotDataModel = new QvisPluginManagerAttributesDataModel(pluginAtts,
        QvisPluginManagerAttributesDataModel::PlotPlugin, this);
    operatorDataModel = new QvisPluginManagerAttributesDataModel(pluginAtts,
        QvisPluginManagerAttributesDataModel::OperatorPlugin, this);
}

// ****************************************************************************
// Method: QvisPluginWindow::SubjectRemoved
//
// Purpose: 
//   This function is called when a subject is removed.
//
// Arguments:
//   TheRemovedSubject : The subject being removed.
//
// Programmer: Jeremy Meredith
// Creation:   January 23, 2008
//
// Modifications:
//   
// ****************************************************************************

void
QvisPluginWindow::SubjectRemoved(Subject *TheRemovedSubject)
{
    if (TheRemovedSubject == pluginAtts)
        pluginAtts = NULL;
    else if (TheRemovedSubject == fileOpenOptions)
        fileOpenOptions = NULL;
}


// ****************************************************************************
//  Method: QvisPluginWindow::CreateWindowContents
//
//  Purpose: 
//    This method creates all of the widgets for the window.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//    Jeremy Meredith, Tue Mar 22 14:02:59 PST 2005
//    Remove the databases tab.
//
//    Jeremy Meredith, Wed Jan 23 15:37:24 EST 2008
//    Enabled contents in the database tab; for this tab, you can
//    not disable plugins, but you can set the default options.
//    Also, made the tab widget resize instead of the empty space
//    when the window grows.
//
//    Dave Pugmire, Wed Feb 13 15:43:24 EST 2008
//    Allow the ability enable/disable DB plugins. Add two buttons to select
//    unselect all. Provide an "X" next to the plugin if read options are available.
//
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
//    Cyrus Harrison, Thu Jul 10 13:58:23 PDT 2008
//    Fixed porting mistake and look and feel of tree widgets.
//
//    Jeremy Meredith, Wed Dec 30 16:44:25 EST 2009
//    Added ability to set preferred file format plugins.
//
//    Brad Whitlock, Mon Feb  8 15:17:25 PST 2010
//    I added operator categories.
//
//    Jeremy Meredith, Wed Aug 18 14:59:57 EDT 2010
//    Updated the text for database plugins preferred format, now that
//    we also try matching preferred plugins before matching non-preferred
//    plugins.  (We still try preferred plugins before giving up even when
//    they don't match the filename.)
//
// ****************************************************************************

void
QvisPluginWindow::CreateWindowContents()
{
    // Create the tab widget.
    QTabWidget *tabs = new QTabWidget(central);
    
    connect(tabs, SIGNAL(currentChanged(int)),
            this, SLOT(tabSelected(int)));
            
    topLayout->addWidget(tabs,10000);

    //
    // Create the plot page
    //
    pagePlots = new QWidget(central);
    QVBoxLayout *plots_layout= new QVBoxLayout(pagePlots);
    tabs->addTab(pagePlots, tr("Plots"));

    plotView = new QTreeView(pagePlots);
    plotView->setModel(plotDataModel);
    plotView->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    plotView->header()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    plots_layout->addWidget(plotView);

    //
    // Create the operator page
    //
    pageOperators = new QWidget(central);
    QVBoxLayout *ops_layout = new QVBoxLayout(pageOperators);
    tabs->addTab(pageOperators, tr("Operators"));
    operatorView = new QTreeView(pageOperators);
    operatorView->setModel(operatorDataModel);
    operatorView->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    operatorView->header()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ops_layout->addWidget(operatorView);

    QHBoxLayout *opsBLayout = new QHBoxLayout();
    ops_layout->addLayout(opsBLayout);
    opsBLayout->addStretch(5);
    clearOperatorCategoryButton = new QPushButton(
        tr("Clear category for all operators"), pageOperators);
    opsBLayout->addWidget(clearOperatorCategoryButton);
    connect(clearOperatorCategoryButton, SIGNAL(clicked()),
            this, SLOT(clearOperatorCategories()));

    //
    // Create the database page
    //
    pageDatabases = new QWidget(central);
    QHBoxLayout *db_toplayout = new QHBoxLayout(pageDatabases);
    QFrame      *db_lframe = new QFrame(pageDatabases);
    db_toplayout->addWidget(db_lframe);
    QVBoxLayout *db_llayout= new QVBoxLayout(db_lframe);
    
    tabs->addTab(pageDatabases, tr("Databases"));

    listDatabases = new QTreeWidget(pageDatabases);
    listDatabases->setRootIsDecorated(false);

    QStringList dbHeaders;
    dbHeaders << tr("Enabled") << tr("Name") << tr("Options") ;
    listDatabases->setHeaderLabels(dbHeaders);
    listDatabases->headerItem()->setTextAlignment(1, Qt::AlignCenter);
    listDatabases->headerItem()->setTextAlignment(2, Qt::AlignCenter);
    listDatabases->header()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    listDatabases->header()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    db_llayout->addWidget(listDatabases);

    QFrame *grpBox = new QFrame(pageDatabases);
    QHBoxLayout *grp_layout = new QHBoxLayout(grpBox);
    grp_layout->setContentsMargins(5,5,5,5);

    // Add select all and unselect all buttons.
    selectAllReadersButton = new QPushButton(tr("Enable all"), grpBox);
    connect(selectAllReadersButton, SIGNAL(clicked()),
            this, SLOT(selectAllReadersButtonClicked()));
    grp_layout->addWidget(selectAllReadersButton);

    unSelectAllReadersButton = new QPushButton(tr("Disable all"), grpBox);
    connect(unSelectAllReadersButton, SIGNAL(clicked()),
            this, SLOT(unSelectAllReadersButtonClicked()));
    grp_layout->addWidget(unSelectAllReadersButton);
    db_llayout->addWidget(grpBox);

    QFrame      *db_rframe = new QFrame(pageDatabases);
    db_toplayout->addWidget(db_rframe);
    QVBoxLayout *db_rlayout= new QVBoxLayout(db_rframe);

    databaseOptionsSetButton = new QPushButton(tr("Set default open options"),
                                               pageDatabases);
    connect(databaseOptionsSetButton, SIGNAL(clicked()),
            this, SLOT(databaseOptionsSetButtonClicked()));
    connect(listDatabases, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), 
            this, SLOT(databaseSelectedItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    
    db_rlayout->addWidget(databaseOptionsSetButton);
    
    dbAddToPreferedButton = new QPushButton(tr("Add to preferred list"),
                                            pageDatabases);
    connect(dbAddToPreferedButton, SIGNAL(clicked()),
            this, SLOT(dbAddToPreferedButtonClicked()));
    db_rlayout->addWidget(dbAddToPreferedButton);

    QGroupBox *preferredGroup = new QGroupBox(tr("Preferred Database Plugins"),
                                              pageDatabases);
    db_rlayout->addWidget(preferredGroup);
    QGridLayout *preferredLayout = new QGridLayout(preferredGroup);

    QLabel *preferredHintLabel = new QLabel(tr(
        "This is an ordered list of plugins which take precedence when "
        "opening files.  When they accept the given file name pattern, these "
        "are tried frst.  And when all attempts to guess based on file "
        "name fail, these are tried before giving up."), preferredGroup);
    preferredHintLabel->setWordWrap(true);
    preferredLayout->addWidget(preferredHintLabel, 0,0, 1,3);

    listPreferredDBs = new QListWidget(preferredGroup);
    preferredLayout->addWidget(listPreferredDBs, 1,0, 1,3);
    connect(listPreferredDBs,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), 
            this,
            SLOT(dbPreferredListItemChanged(QListWidgetItem*,QListWidgetItem*)));
    
    dbPreferredUpButton = new QPushButton(tr("Up"), preferredGroup);
    connect(dbPreferredUpButton, SIGNAL(clicked()),
            this, SLOT(dbPreferredUpButtonClicked()));
    preferredLayout->addWidget(dbPreferredUpButton, 2,0);

    dbPreferredDownButton = new QPushButton(tr("Down"), preferredGroup);
    connect(dbPreferredDownButton, SIGNAL(clicked()),
            this, SLOT(dbPreferredDownButtonClicked()));
    preferredLayout->addWidget(dbPreferredDownButton, 2,1);

    dbPreferredRemoveButton = new QPushButton(tr("Remove"), preferredGroup);
    connect(dbPreferredRemoveButton, SIGNAL(clicked()),
            this, SLOT(dbPreferredRemoveButtonClicked()));
    preferredLayout->addWidget(dbPreferredRemoveButton, 2,2);

    // Show the appropriate page based on the activeTab setting.
    tabs->blockSignals(true);
    tabs->setCurrentIndex(activeTab);
    tabs->blockSignals(false);
}

// ****************************************************************************
// Method: QvisPluginWindow::Update
//
// Purpose:
//     Override the parent so we know when the plugin attributes 
//     have been initialized by the viewer
//
// Programmer: Jeremy Meredith
// Creation:   September 27, 2001
//
// Modifications:
//    Jeremy Meredith, Wed Jan 23 15:38:11 EST 2008
//    Handle two subjects.
//
// ****************************************************************************

void
QvisPluginWindow::Update(Subject *s)
{
    QvisPostableWindowSimpleObserver::Update(s);
    if (s==pluginAtts)
    {
        if (!pluginsInitialized)
        {
            pluginsInitialized = true;
            emit pluginSettingsChanged();
        }
    }
    else if (s==fileOpenOptions)
    {
        // GUI got new file open options
    }
}

// ****************************************************************************
//  Method: QvisPluginWindow::UpdateWindow
//
//  Purpose: 
//    This method is called when the plugin attributes object that the
//    window observes is changed. It is this method's responsibility to set the
//    state of the window's widgets to match the state of the plugin
//    attributes.
//
//  Arguments:
//    doAll : A flag that tells the method to ignore which attributes are
//            selected. All widgets are updated if doAll is true.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//    Brad Whitlock, Thu Sep 6 22:58:34 PST 2001
//    Added checks for Qt's version
//
//    Jeremy Meredith, Fri Sep 28 13:52:35 PDT 2001
//    Added ability to keep track of which items are checked/unchecked.
//
//    Jeremy Meredith, Wed Jan 23 15:38:27 EST 2008
//    Handle two observed subjects, including the new database opening options.
//
//    Jeremy Meredith, Thu Jan 24 09:54:25 EST 2008
//    Forgot to add doAll as a condition to force updates.  Fixed now.
//
//    Cyrus Harrison, Mon Feb  4 09:46:24 PST 2008
//    Resolved AIX linking error w/ auto std::string to QString conversion.
//
//    Dave Pugmire, Wed Feb 13 15:43:24 EST 2008
//    Update the FileOpenOptions for enable/disable DB plugins.
//
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
//    Cyrus Harrison, Tue Jul  8 16:03:44 PDT 2008
//    Fixed problem where database were shown in the operators tab.
//
//    Jeremy Meredith, Wed Dec 30 16:44:25 EST 2009
//    Added ability to set preferred file format plugins.
//
//    Jeremy Meredith, Fri Jan 15 17:08:22 EST 2010
//    Give visual cue when a disabled plugin is preferred.
//
//    Brad Whitlock, Thu Feb  4 16:54:47 PST 2010
//    I rewrote the code for plots and operators so it uses a data model.
// 
//    Justin Privitera, Fri Apr 22 11:55:32 PDT 2022
//    Added case-insensitive alphabetization of database plugin names.
//
// ****************************************************************************

void
QvisPluginWindow::UpdateWindow(bool doAll)
{
    if (doAll || selectedSubject == pluginAtts)
    {
        // Save off the current list of enabled plot & operator plugins.
        enabledPlugins = pluginAtts->GetEnabled();

        int opCount = 0;
        for(size_t i = 0; i < pluginAtts->GetType().size(); ++i)
        {
            if(pluginAtts->GetType()[i] == "operator")
                opCount++;
        }
        clearOperatorCategoryButton->setEnabled(opCount > 0);
    }
    
    if (doAll || selectedSubject == fileOpenOptions)
    {
        listDatabases->clear();
        listDatabases->setSortingEnabled(false);

        databaseItems.clear();
        databaseIndexes.clear();

        // Necessary to sort the plugin names so they appear in 
        // alphabetical case-insensitive order.
        std::vector<std::pair<std::string, int>> plugins;
        for (int i = 0; i < fileOpenOptions->GetNumOpenOptions(); i ++)
        {
            // Here we populate the list of plugin names.
            std::string plugin_name = fileOpenOptions->GetTypeNames()[i].c_str();
            std::transform(
                plugin_name.begin(), 
                plugin_name.end(), 
                plugin_name.begin(),
                [](unsigned char c) { return std::tolower(c); });
            plugins.push_back(std::make_pair(plugin_name, i));
        }

        std::sort(plugins.begin(), plugins.end(),
            [](std::pair<std::string, int> a, std::pair<std::string, int> b)
            {
                return a.first < b.first;
            });

        for (int i = 0; i < plugins.size(); i ++)
        {
            // Now that we have the plugins in the correct order, we can 
            // retrieve the required data and add items to `listDatabases` in
            // the correct order.
            int index = plugins[i].second;
            QTreeWidgetItem *item = new QTreeWidgetItem(listDatabases);
            item->setCheckState(0,fileOpenOptions->GetEnabled()[index] ? Qt::Checked : Qt::Unchecked);

            item->setText(1,fileOpenOptions->GetTypeNames()[index].c_str());

            if (fileOpenOptions->GetOpenOptions(index).GetNumberOfOptions() == 0)
                item->setText(2, "  ");
            else
                item->setText(2, tr("yes"));

            databaseItems.push_back(item);
            databaseIndexes.push_back(index);
        }

        databaseOptionsSetButton->setEnabled(false);
        dbAddToPreferedButton->setEnabled(false);

        listPreferredDBs->clear();
        for (size_t i=0; i<fileOpenOptions->GetPreferredIDs().size(); i++)
        {
            string id = fileOpenOptions->GetPreferredIDs()[i];
            QListWidgetItem *item = new QListWidgetItem(id.c_str(),listPreferredDBs);
            if (!fileOpenOptions->IsIDEnabled(id))
                item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        }
        dbPreferredRemoveButton->setEnabled(false);
        dbPreferredUpButton->setEnabled(false);
        dbPreferredDownButton->setEnabled(false);
    }
}

// ****************************************************************************
//  Method: QvisPluginWindow::Apply
//
//  Purpose: 
//    This method tells the plugin attributes to notify all observers of
//    changes in the object.
//
//  Arguments:
//    dontIgnore : If this is true, the new state takes effect immediately.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//    Jeremy Meredith, Fri Sep 28 13:52:35 PDT 2001
//    Added ability to keep track of which items are checked/unchecked.
//
//    Jeremy Meredith, Fri Mar 19 13:46:31 PST 2004
//    Added warning to inform user about the need to save settings and
//    restart visit to pick up changes to plugins.
//
//    Jeremy Meredith, Wed Jan 23 15:38:46 EST 2008
//    Only issue the warning if the enabled/disabled plugins are changed.
//    Do updates for the default file opening options.
//
//    Dave Pugmire, Wed Feb 13 15:43:24 EST 2008
//    Update the FileOpenOptions for enable/disable DB plugins.
//
//    Brad Whitlock, Tue Apr  8 15:26:49 PDT 2008
//    Support for internationalization.
//
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
//    Brad Whitlock, Tue Feb  9 13:50:28 PST 2010
//    I rewrote the plot and operator portion.
//
// ****************************************************************************

void
QvisPluginWindow::Apply(bool dontIgnore)
{
    // See if the plot and operator enabled states changed.
    bool dirty = pluginAtts->GetEnabled() != enabledPlugins;

    // See if the database plugin enabled states changed.
    for (size_t i=0; i<databaseItems.size(); i++)
    {
        bool newvalue = databaseItems[i]->checkState(0);
        int &value = fileOpenOptions->GetEnabled()[i];
        if (bool(value) != newvalue)
            dirty = true;
        value = newvalue;
    }

    // Notify the viewer about the plugin enabled attributes
    pluginAtts->Notify();

    // And then about the new file opening options
    fileOpenOptions->Notify();
    GetViewerMethods()->SetDefaultFileOpenOptions();

    if (dirty)
    {
        GUIBase::Warning(tr("Note:  Plugins are loaded at startup.  Please save "
                     "your settings and restart VisIt to apply your changes."));
    }
}

// ****************************************************************************
//  Method: QvisPostableWindow::CreateNode
//
//  Purpose: 
//    Writes the window's extra information to the config file.
//
//  Arguments:
//    parentNode : The node to which the window's attributes are added.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//    Jeremy Meredith, Wed Jan 23 15:39:32 EST 2008
//    Handle two observed subjects.
//   
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
// ****************************************************************************

void
QvisPluginWindow::CreateNode(DataNode *parentNode)
{
    // Call the base class's method to save the generic window attributes.
    QvisPostableWindowSimpleObserver::CreateNode(parentNode);

    if(saveWindowDefaults)
    {
        DataNode *node = parentNode->GetNode(windowTitle().toStdString());

        // Save the current tab.
        node->AddNode(new DataNode("activeTab", activeTab));
    }
}

// ****************************************************************************
//  Method: QvisPluginWindow::SetFromNode
//
//  Purpose: 
//    Reads window attributes from the DataNode representation of the config
//    file.
//
//  Arguments:
//    parentNode : The data node that contains the window's attributes.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//    Jeremy Meredith, Wed Jan 23 15:39:32 EST 2008
//    Handle two observed subjects.
//   
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
// ****************************************************************************

void
QvisPluginWindow::SetFromNode(DataNode *parentNode, const int *borders)
{
    DataNode *winNode = parentNode->GetNode(windowTitle().toStdString());
    if(winNode == 0)
        return;

    // Get the active tab and show it.
    DataNode *node;
    if((node = winNode->GetNode("activeTab")) != 0)
    {
        activeTab = node->AsInt();
        if(activeTab != 0 && activeTab != 1 && activeTab != 2)
            activeTab = 0;
    }

    // Call the base class's function.
    QvisPostableWindowSimpleObserver::SetFromNode(parentNode, borders);
}

// ****************************************************************************
//  Method: QvisPluginWindow::apply
//
//  Purpose: 
//    This is a Qt slot function that applies the plugin attributes
//    unconditionally.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//   
// ****************************************************************************

void
QvisPluginWindow::apply()
{
    //SetUpdate(false);
    Apply(true);
}

// ****************************************************************************
//  Method: QvisPluginWindow::tabSelected
//
//  Purpose: 
//    This is a Qt slot function that is called when the tabs are changed.
//
//  Arguments:
//    index : The new active tab.
//
//  Programmer: Jeremy Meredith
//  Creation:   August 31, 2001
//
//  Modifications:
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
// ****************************************************************************

void
QvisPluginWindow::tabSelected(int tab)
{
    activeTab = tab;
}

// ****************************************************************************
// Method: QvisPluginWindow::clearOperatorCategories
//
// Purpose: 
//   This method clears all of the operator categories.
//
// Programmer: Brad Whitlock
// Creation:   Tue Feb  9 13:57:33 PST 2010
//
// Modifications:
//   
// ****************************************************************************

void
QvisPluginWindow::clearOperatorCategories()
{
    stringVector newCat;
    for(size_t j = 0; j < pluginAtts->GetType().size(); ++j)
    {
        if(pluginAtts->GetType()[j] == "operator")
            newCat.push_back("");
        else
            newCat.push_back(pluginAtts->GetCategory()[j]);
    }
    pluginAtts->SetCategory(newCat);
    Apply();
}

// ****************************************************************************
//  Method:  QvisPluginWindow::databaseOptionsSetButtonClicked
//
//  Purpose:
//    Action to take when the user tries to set the default file opening
//    options for the selected plugin.
//
//  Arguments:
//    none
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 23, 2008
//
//  Modifications:
//    Brad Whitlock, Tue Apr  8 15:26:49 PDT 2008
//    Support for internationalization.
//
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
//    Jeremy Meredith, Wed Dec 30 16:44:59 EST 2009
//    Moved some contents to a common function.
// 
//    Justin Privitera, Tue Oct 24 15:37:50 PDT 2023
//    Use index redirection to get at the fileOpenOptions.
//
// ****************************************************************************
void
QvisPluginWindow::databaseOptionsSetButtonClicked()
{
    int index = getCurrentlySelectedDBIndex();
    if (index == -1)
        return;

    DBOptionsAttributes &opts =
        fileOpenOptions->GetOpenOptions(databaseIndexes[index]);
    if (opts.GetNumberOfOptions() > 0)
    {
        QvisDBOptionsDialog *optsdlg = new QvisDBOptionsDialog(&opts, NULL);
        QString caption = tr("Default file opening options for %1 reader").
                          arg(fileOpenOptions->GetTypeNames()[databaseIndexes[index]].c_str());
        optsdlg->setWindowTitle(caption);
        int result = optsdlg->exec();
        delete optsdlg;
        if (result == QDialog::Accepted)
        {
            // We don't need to do anything here:
            //  First, because we set it up so the options dialog sets the
            //  default file opening options if and only if they hit okay.
            //  And second, we wait to notify the viewer about changes
            //  until the user hits Apply.
        }
        else // rejected
        {
            // Again, nothing to do because the options dialog is a
            // complete no-op if the user hit Cancel.
        }
    }
}


// ****************************************************************************
//  Method:  QvisPluginWindow::databaseSelectedItemChanged
//
//  Purpose:
//    Set the enabled state of the button to set the default opening options
//    based on whether or not there are any options to set.
//
//  Arguments:
//    item       the newly highlighted item
//
//  Programmer:  Jeremy Meredith
//  Creation:    January 23, 2008
//
//  Modifications:
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
//    Jeremy Meredith, Wed Dec 30 16:44:59 EST 2009
//    Moved contents to a common function.
//
// ****************************************************************************
void
QvisPluginWindow::databaseSelectedItemChanged(QTreeWidgetItem *item,
                                              QTreeWidgetItem *prev_item)
{
    UpdateWidgetSensitivites();
}

// ****************************************************************************
//  Method:  QvisPluginWindow::selectAllReadersButtonClicked()
//
//  Purpose:
//    Enable all the DB plugins.
//
//  Arguments:
//    none
//
//  Programmer:  Dave Pugmire
//  Creation:    February 13, 2008
//
//  Modifications:
//    Dave Pugmire, Thu Feb 14 14:08:50 EST 2008
//    Bug fix. The message to save settings and restart visit on Apply was not
//    being shown. Just set the checkbox state. No need to call update window.
//
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
// ****************************************************************************
void
QvisPluginWindow::selectAllReadersButtonClicked()
{
    for (size_t i=0; i<databaseItems.size(); i++)
        databaseItems[i]->setCheckState(0,Qt::Checked);
}

// ****************************************************************************
//  Method:  QvisPluginWindow::unSelectAllReadersButtonClicked()
//
//  Purpose:
//    Disable all the DB plugins.
//
//  Arguments:
//    none
//
//  Programmer:  Dave Pugmire
//  Creation:    February 13, 2008
//
//  Modifications:
//    Dave Pugmire, Thu Feb 14 14:08:50 EST 2008
//    Bug fix. The message to save settings and restart visit on Apply was not
//    being shown. Just set the checkbox state. No need to call update window.
//
//    Cyrus Harrison, Tue Jun 24 11:15:28 PDT 2008
//    Initial Qt4 Port.
//
// ****************************************************************************
void
QvisPluginWindow::unSelectAllReadersButtonClicked()
{
    for (size_t i=0; i<databaseItems.size(); i++)
        databaseItems[i]->setCheckState(0,Qt::Unchecked);
}

// ****************************************************************************
// Method:  QvisPluginWindow::dbAddToPreferedButtonClicked
//
// Purpose:
//   callback for the "Add to preferred list"  button
//
// Arguments:
//   none
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// Modifications:
//   Jeremy Meredith, Fri Jan 15 17:08:22 EST 2010
//   Give visual cue when a disabled plugin is preferred.
// 
//   Justin Privitera, Tue Oct 24 15:37:50 PDT 2023
//   Use index redirection to get at the fileOpenOptions.
//
// ****************************************************************************

void
QvisPluginWindow::dbAddToPreferedButtonClicked()
{
    int index = getCurrentlySelectedDBIndex();
    if (index < 0)
        return;

    string id = fileOpenOptions->GetTypeIDs()[databaseIndexes[index]];
    if (! preferredOptionsContainsID(id))
    {
        fileOpenOptions->GetPreferredIDs().push_back(id);
        fileOpenOptions->SelectPreferredIDs();
        QListWidgetItem *item = new QListWidgetItem(id.c_str(),
                                                    listPreferredDBs);
        if (!fileOpenOptions->IsIDEnabled(id))
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        UpdateWidgetSensitivites();
    }
}

// ****************************************************************************
// Method:  QvisPluginWindow::dbPreferredUpButtonClicked
//
// Purpose:
//   callback for the "Up" button in the preferred list
//
// Arguments:
//   none
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// Modifications:
//   Jeremy Meredith, Fri Jan 15 17:08:22 EST 2010
//   Give visual cue when a disabled plugin is preferred.
//
// ****************************************************************************

void
QvisPluginWindow::dbPreferredUpButtonClicked()
{
    vector<string> &preferred = fileOpenOptions->GetPreferredIDs();
    int index = getCurrentlySelectedPreferredIndex();
    if (index < 1)
        return;
    string id = preferred[index];
    preferred[index] = preferred[index-1];
    preferred[index-1] = id;
    fileOpenOptions->SelectPreferredIDs();

    listPreferredDBs->clear();
    for (size_t i=0; i<fileOpenOptions->GetPreferredIDs().size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(preferred[i].c_str(),
                                                    listPreferredDBs);
        if (!fileOpenOptions->IsIDEnabled(preferred[i]))
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
    listPreferredDBs->setCurrentRow(index-1);
    UpdateWidgetSensitivites();
}

// ****************************************************************************
// Method:  QvisPluginWindow::dbPreferredDownButtonClicked
//
// Purpose:
//   callback for the "Down" button in the preferred list
//
// Arguments:
//   remove
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// Modifications:
//   Jeremy Meredith, Fri Jan 15 17:08:22 EST 2010
//   Give visual cue when a disabled plugin is preferred.
//
// ****************************************************************************

void
QvisPluginWindow::dbPreferredDownButtonClicked()
{
    vector<string> &preferred = fileOpenOptions->GetPreferredIDs();
    int index = getCurrentlySelectedPreferredIndex();
    if (index < 0 || (size_t)index >= preferred.size() - 1)
        return;
    string id = preferred[index];
    preferred[index] = preferred[index+1];
    preferred[index+1] = id;
    fileOpenOptions->SelectPreferredIDs();

    listPreferredDBs->clear();
    for (size_t i=0; i<fileOpenOptions->GetPreferredIDs().size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(preferred[i].c_str(),
                                                    listPreferredDBs);
        if (!fileOpenOptions->IsIDEnabled(preferred[i]))
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
    listPreferredDBs->setCurrentRow(index+1);
    UpdateWidgetSensitivites();
}

// ****************************************************************************
// Method:  QvisPluginWindow::dbPreferredRemoveButtonClicked
//
// Purpose:
//   callback for the "Remove" button in the preferred list
//
// Arguments:
//   none
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// Modifications:
//   Jeremy Meredith, Fri Jan 15 17:08:22 EST 2010
//   Give visual cue when a disabled plugin is preferred.
//
// ****************************************************************************

void
QvisPluginWindow::dbPreferredRemoveButtonClicked()
{
    vector<string> &preferred = fileOpenOptions->GetPreferredIDs();
    int index = getCurrentlySelectedPreferredIndex();
    if (index < 0)
        return;
    for (size_t i=index; i<preferred.size()-1; i++)
        preferred[i] = preferred[i+1];
    preferred.pop_back();
    fileOpenOptions->SelectPreferredIDs();
    
    listPreferredDBs->clear();
    for (size_t i=0; i<fileOpenOptions->GetPreferredIDs().size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(preferred[i].c_str(),
                                                    listPreferredDBs);
        if (!fileOpenOptions->IsIDEnabled(preferred[i]))
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
    UpdateWidgetSensitivites();
}

// ****************************************************************************
// Method:  QvisPluginWindow::getCurrentlySelectedDBIndex
//
// Purpose:
//   Get the index in the list of the currently selected db plugin
//
// Arguments:
//   none
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// ****************************************************************************

int
QvisPluginWindow::getCurrentlySelectedDBIndex()
{
    QTreeWidgetItem *item = listDatabases->currentItem();
    if (!item)
        return -1;

    int index = -1;
    for (size_t i=0; i<databaseItems.size(); i++)
    {
        if (item == databaseItems[i])
        {
            index = i;
            break;
        }
    }
    return index;
}

// ****************************************************************************
// Method:  QvisPluginWindow::getCurrentlySelectedPreferredIndex
//
// Purpose:
//   Get the index in the list of the currently selected preferred db plugin
//
// Arguments:
//   none
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// ****************************************************************************

int
QvisPluginWindow::getCurrentlySelectedPreferredIndex()
{
    QListWidgetItem *item = listPreferredDBs->currentItem();
    vector<string> &preferred = fileOpenOptions->GetPreferredIDs();
    if (!item)
        return -1;

    int index = -1;
    for (size_t i=0; i<preferred.size(); i++)
    {
        if (preferred[i] == item->text().toStdString())
        {
            index = i;
            break;
        }
    }
    return index;
}

// ****************************************************************************
// Method:  QvisPluginWindow::preferredOptionsContainsID
//
// Purpose:
//   return true if the given ID is in the current set of preferred db plugins
//
// Arguments:
//   none
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// ****************************************************************************

bool
QvisPluginWindow::preferredOptionsContainsID(const string &id)
{
    for (size_t i=0; i<fileOpenOptions->GetPreferredIDs().size(); i++)
    {
        if (fileOpenOptions->GetPreferredIDs()[i] == id)
            return true;
    }
    return false;
}

// ****************************************************************************
// Method:  QvisPluginWindow::dbPreferredListItemChanged
//
// Purpose:
//   callback when the preferred db plugin list selection changes
//
// Arguments:
//   item, prev_item    the new and old selections
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// ****************************************************************************

void
QvisPluginWindow::dbPreferredListItemChanged(QListWidgetItem *item,
                                             QListWidgetItem *prev_item)
{
    UpdateWidgetSensitivites();
}

// ****************************************************************************
// Method:  QvisPluginWindow::UpdateWidgetSensitivites
//
// Purpose:
//   Set the enabled state of widgets based on the current attributes.
//
// Arguments:
//   none
//
// Programmer:  Jeremy Meredith
// Creation:    December 30, 2009
//
// Modifications:
//   Jeremy Meredith, Mon Jan  4 14:27:17 EST 2010
//   Fixed sensitivity bug.
//
// ****************************************************************************

void
QvisPluginWindow::UpdateWidgetSensitivites()
{
    vector<string> &preferred = fileOpenOptions->GetPreferredIDs();
    int pindex = getCurrentlySelectedPreferredIndex();
    dbPreferredRemoveButton->setEnabled(pindex != -1);
    dbPreferredUpButton->setEnabled(pindex > 0);
    dbPreferredDownButton->setEnabled(pindex >= 0 &&
                                      (size_t)pindex < preferred.size() - 1);

    int dbindex = getCurrentlySelectedDBIndex();
    if (dbindex >= 0)
    {
        const DBOptionsAttributes &opts =
            fileOpenOptions->GetOpenOptions(databaseIndexes[dbindex]);
        databaseOptionsSetButton->setEnabled(opts.GetNumberOfOptions()>0);
        dbAddToPreferedButton->setEnabled(dbindex > 0 &&
            !preferredOptionsContainsID(fileOpenOptions->GetTypeIDs()
                                        [databaseIndexes[dbindex]]));
    }
    else
    {
        databaseOptionsSetButton->setEnabled(false);
        dbAddToPreferedButton->setEnabled(false);
    }
}
