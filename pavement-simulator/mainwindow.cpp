#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* initializing tabs */
    initializeUI();
    /* initializing treeView items */
    initializeTreeView();
    /* menu bar */
    menuBar()->setNativeMenuBar(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ============================================================================
// initialization
// ============================================================================
/* initialize GUI */
void MainWindow::initializeUI()
{
    /* initial condition once the app is opened*/
    ui->tabWidget->setCurrentIndex(0);
    ui->pushButton_2->setText("Add material model");

    /* material tab */
    ui->stackedWidget->setCurrentIndex(0);
    initializeQTable(ui->tableWidget);

    /* interface tab */
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->stackedWidget_3->setCurrentIndex(0);
    initializeQTable(ui->tableWidget_2);

    /* structure tab */

    /* mesh tab */
    ui->lineEdit_31->setEnabled(false);
    ui->lineEdit_32->setEnabled(false);
    ui->lineEdit_33->setEnabled(false);

    /* loading tab */
    ui->stackedWidget_4->setCurrentIndex(0);

    /* analysis tab */
}

/* initialize the table with empty cells */
void MainWindow::initializeQTable(QTableWidget *table)
{
    for(int i = 0; i < table->rowCount(); i = i + 1)
    {
        for(int j = 0; j < table->columnCount(); j = j + 1)
        {
            QTableWidgetItem * aTableItem = new QTableWidgetItem(QString(""));
            if(i==0 && j==1)
            {
                aTableItem->setText(QString("-"));
                aTableItem->setFlags(aTableItem->flags() & ~Qt::ItemIsEditable);
                aTableItem->setFlags(aTableItem->flags() & Qt::ItemIsEditable);
            }
            table->setItem(i,j,aTableItem);
        }
    }

}

/* initialize treeView */
void MainWindow::initializeTreeView()
{ /* initialize tree view model and */

    /* set column titles */
    standardModel.setHorizontalHeaderItem(0, new QStandardItem(" ") );

    /*  items */
    QFont modelItemFont = QApplication::font();
    modelItemFont.setBold(true);

    item_constitutive.setText("Material model");
    item_constitutive.setSelectable( false );
    item_constitutive.setEditable(false);
    item_constitutive.setFont(modelItemFont);

    item_cohesive.setText("Interface model");
    item_cohesive.setSelectable( false );
    item_cohesive.setEditable(false);
    item_cohesive.setFont(modelItemFont);

    item_structure.setText("Structure");
    item_structure.setSelectable( false );
    item_structure.setEditable(false);
    item_structure.setFont(modelItemFont);

    item_mesh.setText("Mesh");
    item_mesh.setSelectable( false );
    item_mesh.setEditable(false);
    item_mesh.setFont(modelItemFont);

    item_load.setText("Load");
    item_load.setSelectable( false );
    item_load.setEditable(false);
    item_load.setFont(modelItemFont);

    item_analysis.setText("Analysis");
    item_analysis.setSelectable( false );
    item_analysis.setEditable(false);
    item_analysis.setFont(modelItemFont);

    // ........................................................................
    /* make "Perfect bond" and "No bond" cohesive models*/
    for(int i=1; i<=2; i=i+1)
    {
        QString label;
        double factor = 0.0;
        int set = 1;
        if(i==1)
        { /* define allbonded coh */
            label = "Perfect bond";
            factor = 1.0e18;
            set = 1;
        }
        else if(i==2)
        {/* define allbonded coh */
            label = "No bond";
            factor = 1.0e-10;
            set = 2;
        }

        modelCohesive aCohesive;

        aCohesive.label = label;
        aCohesive.cohType = 1;
        aCohesive.cohSet = set;

        aCohesive.czVERelaxModuInf = factor;
        aCohesive.czVERelaxModuPS << factor * 1.0;
        aCohesive.czVERelaxTimePS << 1.0;

        aCohesive.czDeltaN = 1.0;
        aCohesive.czDeltaT = 1.0;
        aCohesive.czSigmaN = 0.0;
        aCohesive.czSigmaT = 0.0;

        aCohesive.bondingDamageIndex = 1;
        aCohesive.czDamagePowerFunC = 1e-10;
        aCohesive.czDamagePowerFunN = 1;
        aCohesive.czDamagePowerFunM = 1;

        /* create qvariant */
        QVariant aVariant;
        aVariant.setValue(aCohesive);

        /* update model tree */
        QStandardItem* aChild = new QStandardItem;
        aChild->setText( aVariant.value<modelCohesive>().label);
        aChild->setData( aVariant, Qt::UserRole + 2);

        item_cohesive.appendRow(aChild);
        item_cohesive.child(item_cohesive.rowCount()-1,0)->setEditable(false);
    }

    // ------------------------------------------------------------------------
    /* populate model */
    standardModel.setItem(0,0,&item_constitutive);
    standardModel.setItem(1,0,&item_cohesive);
    standardModel.setItem(2,0,&item_structure);
    standardModel.setItem(3,0,&item_mesh);
    standardModel.setItem(4,0,&item_load);
    standardModel.setItem(5,0,&item_analysis);

    /* showing treeView */
    ui->treeView->setModel(&standardModel);
    ui->treeView->expandAll();
}

// ============================================================================
// UI update
// ============================================================================
/* tab bar is changed*/
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0)
    {
        ui->pushButton_2->setText("Confirm material model");
    }
    else if(index == 1)
    {
        ui->pushButton_2->setText("Confirm interface model");
    }
    else if(index == 2)
    {/* model structure tab */

        ui->pushButton_2->setText("Confirm layer");

        /* populate material models */
        QStringList list;
        if(item_constitutive.hasChildren())
        {
            for(int i = 0; i < item_constitutive.rowCount(); i = i +1)
            {
                list << item_constitutive.child(i,0)->text();
            }
        }
        ui->comboBox_4->clear();
        ui->comboBox_4->addItems(list);

        /* populate interface models onto combobox */
        list.clear();
        if(item_cohesive.hasChildren())
        {
            for(int i = 0; i < item_cohesive.rowCount(); i = i +1)
            {
                list << item_cohesive.child(i,0)->text();
            }
        }
        ui->comboBox_7->clear();
        ui->comboBox_7->addItems(list);

        ui->comboBox_8->clear();
        ui->comboBox_8->addItems(list);
    }
    else if(index == 3)
    {
        ui->pushButton_2->setText("Confirm mesh");
    }
    else if(index == 4)
    {
        ui->pushButton_2->setText("Confirm loading");
    }
    else if(index == 5)
    {
        ui->pushButton_2->setText("Confirm time");
    }
}

/* combobox - choose constitutive model type */
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {/* select*/
        ui->stackedWidget->setEnabled(false);
        ui->stackedWidget->setCurrentIndex(0);
    }else if(index == 1)
    {/* elastic*/
        ui->stackedWidget->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(1);
    }else if(index == 2)
    {/* viscoelastic */
        ui->stackedWidget->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(2);
    }
}
/* combobox - choose cohesive model type */
void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if(index == 0)
    {/* select*/
        ui->stackedWidget_2->setEnabled(false);
        ui->stackedWidget_2->setCurrentIndex(0);
    }else if(index == 1)
    {/* VE */
        ui->stackedWidget_2->setEnabled(true);
        ui->stackedWidget_2->setCurrentIndex(1);
    }
}
/* combobox - choose damage model type */
void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    if(index == 0)
    {/* select*/
        ui->stackedWidget_3->setEnabled(false);
        ui->stackedWidget_3->setCurrentIndex(0);
    }else if(index == 1)
    {/* power*/
        ui->stackedWidget_3->setEnabled(true);
        ui->stackedWidget_3->setCurrentIndex(1);
    }else if(index == 2)
    {/* gaussian */
        ui->stackedWidget_3->setEnabled(true);
        ui->stackedWidget_3->setCurrentIndex(2);
    }
}
/* combobox - choose loading type */
void MainWindow::on_comboBox_9_currentIndexChanged(int index)
{
    if(index == 0)
    {/* select*/
        ui->stackedWidget_4->setDisabled(true);
        ui->stackedWidget_4->setCurrentIndex(0);
    }else if(index == 1)
    {/* elastic*/
        ui->stackedWidget_4->setEnabled(true);
        ui->stackedWidget_4->setCurrentIndex(1);
    }
    else if(index == 2)
    {/* elastic*/
        ui->stackedWidget_4->setEnabled(true);
        ui->stackedWidget_4->setCurrentIndex(2);
    }
}

/* label - when new layer is going to be defined */
void MainWindow::on_lineEdit_17_editingFinished()
{
    if(item_structure.rowCount()==0)
    {
        ui->comboBox_7->setEnabled(false);
        ui->label_21->setEnabled(false);
    }
    else
    {
        ui->comboBox_7->setEnabled(true);
        ui->label_21->setEnabled(true);
    }
}

// ============================================================================
// confirm and delete
// ============================================================================
/* confirm button */
void MainWindow::on_pushButton_2_clicked()
{
    /* updates input vectors*/
    if(ui->tabWidget->currentIndex() == 0)
    {
        getConstitutiveInput();
    }
    else if(ui->tabWidget->currentIndex() == 1)
    {
        getCohesiveInput();
    }
    else if(ui->tabWidget->currentIndex() == 2)
    {
        getStructureInput();
    }
    else if(ui->tabWidget->currentIndex() == 3)
    {
        getMeshInput();
    }
    else if(ui->tabWidget->currentIndex() == 4)
    {
        getLoadingInput();
    }
    else if(ui->tabWidget->currentIndex() == 5)
    {
        getTimeInput();
    }

    /* update model plot */
    dialogPlotMesh.update();
}

/* delete button */
void MainWindow::on_pushButton_clicked()
{
    QModelIndex selectedItemIndex = ui->treeView->selectionModel()->currentIndex();
    QStandardItem* selectedItem = standardModel.itemFromIndex(selectedItemIndex);

    /*  if material or inteface is removed:
     *  remove structure */
    if(selectedItem->parent()->row() == 0 ||
       selectedItem->parent()->row() == 1 )
    {
        /* remodve existing structure*/
        if(item_structure.rowCount() != 0)
        {
            item_structure.removeRows(0,item_structure.rowCount());
        }
    }

    /* delete item */
    if(selectedItem->parent() == nullptr )
    {/* if main items are selected */
        return;
    }
    else
    {/* if sub-item is selected */
        selectedItem->parent()->removeRow(selectedItemIndex.row());
    }

}

// ============================================================================
// read inputs
// ============================================================================
/* get constitutive inputs */
void MainWindow::getConstitutiveInput()
{
    /* constitutive tab */
    if(ui->comboBox->currentIndex() == 0)
    {/*  */
        QMessageBox::warning(this, " ", "Please select a constitutive model.");
    }else
    {
        /* create a constitutive struct */
        modelConstitutive aConstitutive;

        /* get material general info */
        aConstitutive.label = ui->lineEdit->text();

        /* check the lable
            new : -1
            old : else */
        int sameLabelChild = isStrChildMember(&item_constitutive, ui->lineEdit->text());

        if(ui->comboBox->currentIndex() ==1)
        {/* get materila elastic */
            aConstitutive.matType = 1;

            aConstitutive.elElasticModulus = ui->lineEdit_2->text().toDouble();
            aConstitutive.elPoissonRatio = ui->lineEdit_3->text().toDouble();
        }else if(ui->comboBox->currentIndex() == 2)
        {/* get materila elastic */
            aConstitutive.matType = 2;

            aConstitutive.veRelaxModuInf = ui->tableWidget->item(0,0)->text().toDouble();

            aConstitutive.veRelaxModuPS = readFromTable(ui->tableWidget, 1, 0);
            aConstitutive.veRelaxTimePS = readFromTable(ui->tableWidget, 1, 1);

            aConstitutive.vePoissonRatio = ui->lineEdit_5->text().toDouble();
        }

        /* find set */
        int matSet_ve = 1;
        int matSet_e = 1;

        for(int i = 0; i < item_constitutive.rowCount(); i = i+1)
        {
            if(item_constitutive.child(i,0)->data(Qt::UserRole + 1).value<modelConstitutive>().matType == 1)
            {/* elastic */
                matSet_e = matSet_e + 1;
            }
            else
            {/* viscoelastic */
                matSet_ve = matSet_ve + 1;
            }
        }
        /* modify set */
        if(sameLabelChild != -1)
        {/* duplicate label */
            matSet_e = matSet_e - 1;
            matSet_ve = matSet_ve - 1;
        }
        if(aConstitutive.matType == 1)
        {/* elastic */
            aConstitutive.matSet = matSet_e;
        }
        else
        {/* viscoelastic */
            aConstitutive.matSet = matSet_ve;
        }

        /* create qvariant */
        QVariant aVariant;
        aVariant.setValue(aConstitutive);

        /* update model tree */
        QStandardItem * aChild = new QStandardItem;
        aChild->setText( aVariant.value<modelConstitutive>().label);
        aChild->setData( aVariant, Qt::UserRole + 1);

        /* add */
        if( sameLabelChild == -1)
        {/* new lable */
            item_constitutive.appendRow(aChild);
        }
        else
        {/* duplicated lable */
            item_constitutive.setChild(sameLabelChild, aChild);
        }
        item_constitutive.child(item_constitutive.rowCount()-1,0)->setEditable(false);
    }
}

/* get cohesive inputs */
void MainWindow::getCohesiveInput()
{
    /* constitutive tab */
    if(ui->comboBox_2->currentIndex() == 0)
    {/*  */
        QMessageBox::warning(this, " ", "Please select a cohesive model.");
    }else if(ui->comboBox_3->currentIndex() == 0)
    {
        QMessageBox::warning(this, " ", "Please select a damage model.");
    }else
    {
        /* add cohesive struct */
        modelCohesive aCohesive;

        /* get general info */
        aCohesive.label = ui->lineEdit_4->text();

        /* check the lable
            new : -1
            old : else */
        int sameLabelChild = isStrChildMember(&item_cohesive, ui->lineEdit_4->text());

        if(ui->comboBox_2->currentIndex() ==1)
        {/* get chesive zone model */
            aCohesive.cohType = 1;

            aCohesive.czVERelaxModuInf = ui->tableWidget_2->item(0,0)->text().toDouble();

            aCohesive.czVERelaxModuPS = readFromTable(ui->tableWidget_2, 1, 0);
            aCohesive.czVERelaxTimePS = readFromTable(ui->tableWidget_2, 1, 1);

            aCohesive.czDeltaN = ui->lineEdit_13->text().toDouble();
            aCohesive.czDeltaT = ui->lineEdit_14->text().toDouble();
            aCohesive.czSigmaN = ui->lineEdit_15->text().toDouble();
            aCohesive.czSigmaT = ui->lineEdit_16->text().toDouble();

            /* damage model */
            if (ui->comboBox_3->currentIndex() == 1)
            {/* power function */
                aCohesive.bondingDamageIndex = 1;

                aCohesive.czDamagePowerFunC = ui->lineEdit_6->text().toDouble();
                aCohesive.czDamagePowerFunN = ui->lineEdit_7->text().toDouble();
                aCohesive.czDamagePowerFunM = ui->lineEdit_8->text().toDouble();
            }else if (ui->comboBox_3->currentIndex() == 2)
            {/* gaussian function */
                aCohesive.bondingDamageIndex = 2;

                aCohesive.czDamageGaussFunA = ui->lineEdit_9->text().toDouble();
                aCohesive.czDamageGaussFunM = ui->lineEdit_10->text().toDouble();
                aCohesive.czDamageGaussFunL = ui->lineEdit_11->text().toDouble();
                aCohesive.czDamageGaussFunD = ui->lineEdit_12->text().toDouble();
            }
        }

        /* find set */
        int matSet_vecz = 1;
        for(int i = 0; i < item_cohesive.rowCount(); i = i+1)
        {
            if(item_cohesive.child(i,0)->data(Qt::UserRole + 2).value<modelCohesive>().cohType == 1)
            {
                matSet_vecz = matSet_vecz + 1;
            }
        }
        /* modify set */
        if( sameLabelChild != -1)
        {/* duplicated lable */
            matSet_vecz = matSet_vecz - 1;
        }
        aCohesive.cohSet = matSet_vecz;

        /* create qvariant */
        QVariant aVariant;
        aVariant.setValue(aCohesive);

        /* update model tree */
        QStandardItem * aChild = new QStandardItem;
        aChild->setText( aVariant.value<modelCohesive>().label);
        aChild->setData( aVariant, Qt::UserRole + 2);


        /* add */
        if( sameLabelChild == -1)
        {/* new lable */
            item_cohesive.appendRow(aChild);
        }
        else
        {/* duplicated lable */
            item_cohesive.setChild(sameLabelChild, aChild);
        }
        item_cohesive.child(item_cohesive.rowCount()-1,0)->setEditable(false);
    }
}

/* get layer input */
void MainWindow::getStructureInput()
{   
    if(ui->comboBox_4->count() == 0)
    {/*  */
        QMessageBox::warning(this, " ", "Constitutive models list is empty.");
    }
    else if(ui->comboBox_7->count() == 0)
    {/*  */
        QMessageBox::warning(this, " ", "Cohesive models list is empty.");
    }
    else
    {/*  */
        /* check layers width*/
        if(item_structure.rowCount() > 0 )
        {
            modelLayer theLayer = item_structure.child(0,0)->data(Qt::UserRole + 3).value<modelLayer>();
            double dummy = ui->lineEdit_19->text().toDouble();
            if( qFabs( theLayer.width - dummy ) > eps )
            {
                QMessageBox::warning(this, " ", "The layers width must be equal."
                                                "In order to modify the layer, delete the layer and add a new one.");
                return;
            }
        }
        /* create a layer struct */
        modelLayer aLayer;

        /* get material general info */
        aLayer.label = ui->lineEdit_17->text();
        aLayer.thickness = ui->lineEdit_18->text().toDouble();
        aLayer.width = ui->lineEdit_19->text().toDouble();

        /* corresponding constitutive model */
        for(int i = 0; i < item_constitutive.rowCount(); i = i+1)
        {
            modelConstitutive theCons = item_constitutive.child(i,0)->data(Qt::UserRole + 1).value<modelConstitutive>();
            if(theCons.label == ui->comboBox_4->currentText())
            {
                aLayer.constitutiveModel = theCons;
            }
        }

        /* bottom bonding and midline bonding models */
        for(int i = 0; i < item_cohesive.rowCount(); i = i+1)
        {
            modelCohesive theCohs = item_cohesive.child(i,0)->data(Qt::UserRole + 2).value<modelCohesive>();
            if(theCohs.label == ui->comboBox_8->currentText())
            {
                aLayer.midlineCohModel = theCohs;
            }
            if(theCohs.label == ui->comboBox_7->currentText())
            {
                aLayer.bottomCohModel = theCohs;
            }
        }

        /* create qvariant */
        QVariant aVariant;
        aVariant.setValue(aLayer);

        /* update model tree */
        QStandardItem * aChild = new QStandardItem;
        aChild->setText( aVariant.value<modelLayer>().label);
        aChild->setData( aVariant, Qt::UserRole + 3);

        /* check if duplicate lable is used */
        int sameLabelChild = isStrChildMember(&item_structure, ui->lineEdit_17->text());
        if( sameLabelChild == -1)
        {/* new lable */

            item_structure.appendRow(aChild);

            /* remodve existing mesh*/
            if(item_mesh.rowCount() != 0)
            {
                item_mesh.takeRow(0);
            }
        }
        else
        {/* duplicated lable */
            item_structure.setChild(sameLabelChild, aChild);
        }
        item_structure.child(item_structure.rowCount()-1,0)->setEditable(false);
    }
}

/* get mesh input */
void MainWindow::getMeshInput()
{
    // -------------------------------------------------------------------------
    /* 1. mesh sublayers:
                each sublayer is half of a layer
                start from bottom layer to top
                start from left sublayer to right
         2. plot mesh
      */

    /* find min layer dimension */
    double minLayreDimension = 1e20;
    for(int i = 0; i < item_structure.rowCount(); i = i + 1)
    {
        modelLayer theLayer = item_structure.child(i,0)->data(Qt::UserRole + 3).value<modelLayer>();
        if(minLayreDimension > theLayer.thickness)
        {
            minLayreDimension = theLayer.thickness;
        }
        else if(minLayreDimension > theLayer.width/2)
        {
            minLayreDimension = theLayer.width/2;
        }
    }

    std::vector<meshSubLayer> meshSubLayers;
    std::vector<meshSubLayer> meshLayers;

    if (item_structure.rowCount() == 0)
    {/**/
        QMessageBox::warning(this, " ", "No layers are defined.");
        return;
    }
    else if(ui->lineEdit_20->text().toDouble() > minLayreDimension)
    {
        QMessageBox::warning(this, " ", "Mesh size is too large.");
        return;
    }
    else
    {/*  */

        double meshSize = ui->lineEdit_20->text().toDouble();
        double bottomOfLayerZ = 0;

        for(int i = 0; i < item_structure.rowCount(); i=i+1)
        {
            modelLayer theLayer = item_structure.child(i,0)->data(Qt::UserRole + 3).value<modelLayer>();

            // ................................................................
            /* mesh the left side */
            double x_min = 0;
            double x_max = theLayer.width/2;
            double z_min = bottomOfLayerZ;
            double z_max = bottomOfLayerZ + theLayer.thickness;

            Matrix pa_x_l = progression_arithmetic(x_min, x_max, meshSize);
            Matrix pa_z_l = progression_arithmetic(z_min, z_max, meshSize);

            meshSubLayer meshSubLayer_l = meshSubLayer(pa_x_l, pa_z_l, "slash", theLayer);

            meshSubLayers.push_back(meshSubLayer_l);

            // ................................................................
            /* mesh the right side*/
            x_min = theLayer.width/2;
            x_max = theLayer.width;
            z_min = bottomOfLayerZ;
            z_max = bottomOfLayerZ + theLayer.thickness;

            Matrix pa_x_r = progression_arithmetic(x_min, x_max, meshSize);
            Matrix pa_z_r = progression_arithmetic(z_min, z_max, meshSize);

            meshSubLayer meshSubLayer_r = meshSubLayer(pa_x_r, pa_z_r, "backSlash", theLayer);

            meshSubLayers.push_back(meshSubLayer_r);

            /* update bottomOfLayerZ*/
            bottomOfLayerZ = bottomOfLayerZ + theLayer.thickness;
        }
    }
    // ------------------------------------------------------------------------
    /* merge sublayer meshes
       meshSubLayers 0 -> bottom left
       meshSubLayers end -> top right
    */

    /* merge left and right sublayers */
    for(unsigned i = 0; i < meshSubLayers.size(); i = i + 2)
    {
        int layerNumber = qFloor(i/2);
        modelLayer theLayer = item_structure.child(layerNumber,0)->data(Qt::UserRole + 3).value<modelLayer>();
        int mbt = theLayer.midlineCohModel.cohSet;

        meshmerge layerMergedMesh = meshmerge(meshSubLayers[i], "right", meshSubLayers[i+1], "left", mbt);
        meshSubLayer meshLayer = meshSubLayer(layerMergedMesh.cooM, layerMergedMesh.conM, layerMergedMesh.cohM);
        meshLayers.push_back(meshLayer);
    }

    /* merge layers */
    Matrix coo = meshLayers[0].coo;
    Matrix con = meshLayers[0].con;
    Matrix coh = meshLayers[0].coh;

    meshSubLayer totalMergedMesh = meshSubLayer(coo, con, coh);

    for(unsigned i = 1; i < meshLayers.size(); i = i + 1)
    {
        int layerNumber = static_cast<int>(i);
        int bbt = item_structure.child(layerNumber,0)->data(Qt::UserRole + 3).value<modelLayer>().bottomCohModel.cohSet;
        meshmerge tempMergedMesh = meshmerge(totalMergedMesh, "top", meshLayers[i], "bottom", bbt);

        totalMergedMesh.coo = tempMergedMesh.cooM;
        totalMergedMesh.con = tempMergedMesh.conM;
        totalMergedMesh.coh = tempMergedMesh.cohM;
    }

    // ------------------------------------------------------------------------
    /* save mesh data in model*/
    modelMesh aMesh;

    aMesh.meshSize = ui->lineEdit_20->text().toDouble();
    aMesh.coo_global = totalMergedMesh.coo;
    aMesh.con_bulk = totalMergedMesh.con;
    aMesh.con_coh = totalMergedMesh.coh;

    aMesh.numOfNodes = Size(aMesh.coo_global,1);
    aMesh.numOfBulkEl = Size(aMesh.con_bulk,1);
    aMesh.numOfIntEl = Size(aMesh.con_coh,1);

    ui->lineEdit_31->setText(QString::number(aMesh.numOfNodes));
    ui->lineEdit_32->setText(QString::number(aMesh.numOfBulkEl));
    ui->lineEdit_33->setText(QString::number(aMesh.numOfIntEl));

    /* create qvariant */
    QVariant aVariant;
    aVariant.setValue(aMesh);

    /* update model tree */
    QStandardItem * aChild = new QStandardItem;
    QString str = QString("ms = %1").arg(aVariant.value<modelMesh>().meshSize);
    aChild->setText( str );
    aChild->setData( aVariant, Qt::UserRole + 4);

    if(item_mesh.rowCount() != 0)
    {
        item_mesh.takeRow(0);
    }
    item_mesh.appendRow(aChild);
    item_mesh.child(item_mesh.rowCount()-1,0)->setEditable(false);
}

/* get loading input */
void MainWindow::getLoadingInput()
{
    if(ui->comboBox_9->currentIndex() == 0)
    {/*  */
        QMessageBox::warning(this, " ", "Please select loading type.");
    }else
    {
        /* check load type - it must be the same as previous loads */
        if(item_load.rowCount() > 0 )
        {
            modelLoading theLoad = item_load.child(0,0)->data(Qt::UserRole + 5).value<modelLoading>();
            if(  theLoad.loadingType != ui->comboBox_9->currentText())
            {
                QMessageBox::warning(this, " ", "The loading type can not be changed. "
                                                "In order to modify the loading, delete the loading and add a new one.");
                return;
            }
            else
            {
                if( "Sine" == ui->comboBox_9->currentText() )
                {/* sine-pulse */
                    if( qFabs( theLoad.amplitude - ui->lineEdit_29->text().toDouble() ) > eps ||
                            qFabs( theLoad.s_cycleDuration - ui->lineEdit_30->text().toDouble() ) > eps )
                    {
                        QMessageBox::warning(this, " ", "Only load amplitude can be changed."
                                                        "In order to modify the loading, delete the loading and add a new one.");
                        return;
                    }
                }
                else if( "Sine-Pulse" == ui->comboBox_9->currentText() )
                {/* sine */
                    if( qFabs( theLoad.amplitude - ui->lineEdit_21->text().toDouble() ) > eps ||
                            qFabs( theLoad.sp_pulseDuration - ui->lineEdit_22->text().toDouble() ) > eps ||
                            qFabs( theLoad.sp_cycleDuration - ui->lineEdit_23->text().toDouble() ) > eps )
                    {
                        QMessageBox::warning(this, " ", "Only load amplitude can be changed."
                                                        "In order to modify the loading, delete the loading and add a new one.");
                        return;
                    }
                }
            }
        }

        /* create a layer struct */
        modelLoading aLoad;

        /* get material general info */
        aLoad.label = ui->lineEdit_24->text();
        aLoad.loadingType = ui->comboBox_9->currentText();

        aLoad.tireCentCoo = ui->lineEdit_28->text().toDouble();
        aLoad.tireWidth = ui->lineEdit_27->text().toDouble();

        /* Sine loading */
        if(ui->comboBox_9->currentText() == "Sine")
        {
            aLoad.amplitude = ui->lineEdit_29->text().toDouble();
            aLoad.s_cycleDuration = ui->lineEdit_30->text().toDouble();
        }
        /* Sine-Pulse loading */
        else if(ui->comboBox_9->currentText() == "Sine-Pulse")
        {
            aLoad.amplitude = ui->lineEdit_21->text().toDouble();
            aLoad.sp_pulseDuration = ui->lineEdit_22->text().toDouble();
            aLoad.sp_cycleDuration = ui->lineEdit_23->text().toDouble();
            if(aLoad.sp_pulseDuration > aLoad.sp_cycleDuration)
            {/* duplicated lable */
                QMessageBox::warning(this, " ", "Pulse duration is bigger than cycle duration.");
                return;
            }
        }

        /* create qvariant */
        QVariant aVariant;
        aVariant.setValue(aLoad);

        /* update model tree */
        QStandardItem * aChild = new QStandardItem;
        aChild->setText( aVariant.value<modelLoading>().label);
        aChild->setData( aVariant, Qt::UserRole + 5);


        /* check if duplicate lable is used */
        int sameLabelChild = isStrChildMember(&item_load, ui->lineEdit_24->text());
        if( sameLabelChild == -1)
        {/* new lable */
            item_load.appendRow(aChild);
        }
        else
        {/* duplicated lable */
            item_load.setChild(sameLabelChild, aChild);
        }
        item_load.child(item_load.rowCount()-1,0)->setEditable(false);
    }
}

/* get time inputs */
void MainWindow::getTimeInput()
{
    /* constitutive tab */
    if(ui->lineEdit_25->text().isEmpty() || ui->lineEdit_26->text().isEmpty())
    {/*  */
        QMessageBox::warning(this, " ", "Please specify simulation time duration and time step.");
    }else
    {/*  */
        if( ui->lineEdit_25->text().toDouble() < ui->lineEdit_26->text().toDouble())
        {/* duplicated lable */
            QMessageBox::warning(this, " ", "Duration time should not exceed time increment.");
        }
        else
        {
            modelTime aSimTime;
            aSimTime.totalTime = ui->lineEdit_25->text().toDouble();
            aSimTime.timeIncrement = ui->lineEdit_26->text().toDouble();


            /* create qvariant */
            QVariant aVariant;
            aVariant.setValue(aSimTime);

            /* update model tree */
            QStandardItem * aChild = new QStandardItem;
            QString str = QString("st = %1").arg(aVariant.value<modelTime>().timeIncrement);
            aChild->setText( str);
            aChild->setData( aVariant, Qt::UserRole + 6);

            /* delete old child */
            if(item_analysis.rowCount() != 0)
            {
                item_analysis.removeRows(0, item_analysis.rowCount() );
            }
            item_analysis.appendRow(aChild);
            item_analysis.child(item_analysis.rowCount()-1,0)->setEditable(false);
        }
    }
}

// ============================================================================
//
// ============================================================================
/* menu bar actions*/
void MainWindow::on_actionOpen_triggered()
{
    loadFromBin();
}

void MainWindow::on_actionSave_triggered()
{
    saveToBin();
}

void MainWindow::on_actionWriteinput_triggered()
{
    writeInputfile();
}

void MainWindow::on_actionRun_triggered()
{
    runFESolver();
}

void MainWindow::on_actionPlot_model_triggered()
{
    visualizeModel();
}
// ----------------------------------------------------------------------------
/* save the project in a binary file */
void MainWindow::saveToBin()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Save Project File"), "",
           tr("Project File (*.bin);;All Files (*)"));

    if (fileName.isEmpty())
    {
            return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        else
        {
            QDataStream save(&file);
            save.setVersion(QDataStream::Qt_4_6);

            int itemRowCount;

            itemRowCount = item_constitutive.rowCount();
            save << itemRowCount;
            for(int i=0; i < item_constitutive.rowCount(); i = i+1)
            {
                modelConstitutive theConstitutive = item_constitutive.child(i,0)->data(Qt::UserRole + 1).value<modelConstitutive>();
                save << theConstitutive;
            }

            itemRowCount = item_cohesive.rowCount();
            save << itemRowCount;
            for(int i=0; i < item_cohesive.rowCount(); i = i+1)
            {
                modelCohesive theCohesive = item_cohesive.child(i,0)->data(Qt::UserRole + 2).value<modelCohesive>();
                save << theCohesive;
            }

            itemRowCount = item_structure.rowCount();
            save << itemRowCount;
            for(int i=0; i < item_structure.rowCount(); i = i+1)
            {
                modelLayer theLayer = item_structure.child(i,0)->data(Qt::UserRole + 3).value<modelLayer>();
                save << theLayer;
            }

            itemRowCount = item_load.rowCount();
            save << itemRowCount;
            for(int i=0; i < item_load.rowCount(); i = i+1)
            {
                modelLoading theLoad = item_load.child(i,0)->data(Qt::UserRole + 5).value<modelLoading>();
                save << theLoad;
            }

            itemRowCount = item_analysis.rowCount();
            save << itemRowCount;
            for(int i=0; i < item_analysis.rowCount(); i = i+1)
            {
                modelTime theSimTime = item_analysis.child(i,0)->data(Qt::UserRole + 6).value<modelTime>();
                save << theSimTime;
            }

            file.close();
        }
    }
}

/* load the project from a binary file */
void MainWindow::loadFromBin()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Project File"), "",
            tr("Project File (*.bin);;All Files (*)"));
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        else
        {

            QDataStream load(&file);
            load.setVersion(QDataStream::Qt_4_6);

            int dummy;

            if(item_constitutive.rowCount() != 0) // empty item_constitutive
            {
                item_constitutive.removeRows(0, item_constitutive.rowCount() );
            }
            load >> dummy; // get number of constitutive models
            for(int i=0; i < dummy; i = i+1)
            {
                modelConstitutive theConstitutive;
                load >> theConstitutive;

                QVariant aVariant;
                aVariant.setValue(theConstitutive);

                QStandardItem * aChild = new QStandardItem;
                aChild->setText( aVariant.value<modelConstitutive>().label );
                aChild->setData( aVariant, Qt::UserRole + 1 );
                item_constitutive.appendRow(aChild);
                item_constitutive.child(item_constitutive.rowCount()-1,0)->setEditable(false);
            }

            if(item_cohesive.rowCount() != 0) // empty item_constitutive
            {
                item_cohesive.removeRows(0, item_cohesive.rowCount() );
            }
            load >> dummy;
            for(int i=0; i < dummy; i = i+1)
            {
                modelCohesive theCohesive;
                load >> theCohesive;

                QVariant aVariant;
                aVariant.setValue(theCohesive);

                QStandardItem * aChild = new QStandardItem;
                aChild->setText( aVariant.value<modelCohesive>().label);
                aChild->setData( aVariant, Qt::UserRole + 2);
                item_cohesive.appendRow(aChild);
                item_cohesive.child(item_cohesive.rowCount()-1,0)->setEditable(false);
            }

            if(item_structure.rowCount() != 0) // empty item_constitutive
            {
                item_structure.removeRows(0, item_structure.rowCount() );
            }
            load >> dummy;
            for(int i=0; i < dummy; i = i+1)
            {
                modelLayer theLayer;
                load >> theLayer;

                QVariant aVariant;
                aVariant.setValue(theLayer);

                QStandardItem * aChild = new QStandardItem;
                aChild->setText( aVariant.value<modelLayer>().label);
                aChild->setData( aVariant, Qt::UserRole + 3);
                item_structure.appendRow(aChild);
                item_structure.child(item_structure.rowCount()-1,0)->setEditable(false);
            }

            if(item_load.rowCount() != 0) // empty item_constitutive
            {
                item_load.removeRows(0, item_load.rowCount() );
            }
            load >> dummy;
            for(int i=0; i < dummy; i = i+1)
            {
                modelLoading theLoad;
                load >> theLoad;

                QVariant aVariant;
                aVariant.setValue(theLoad);

                QStandardItem * aChild = new QStandardItem;
                aChild->setText( aVariant.value<modelLoading>().label);
                aChild->setData( aVariant, Qt::UserRole + 5);
                item_load.appendRow(aChild);
                item_load.child(item_load.rowCount()-1,0)->setEditable(false);
            }

            if(item_analysis.rowCount() != 0) // empty item_analysis
            {
                item_analysis.removeRows(0, item_analysis.rowCount() );
            }
            load >> dummy;
            for(int i=0; i < dummy; i = i+1)
            {
                modelTime theSimTime;
                load >> theSimTime;

                QVariant aVariant;
                aVariant.setValue(theSimTime);

                QStandardItem * aChild = new QStandardItem;
                QString str = QString("st = %1").arg(aVariant.value<modelTime>().timeIncrement);
                aChild->setText( str );
                aChild->setData( aVariant, Qt::UserRole + 6);
                item_analysis.appendRow(aChild);
                item_analysis.child(item_analysis.rowCount()-1,0)->setEditable(false);
            }

            /* populate model */
            standardModel.setItem(0,0,&item_constitutive);
            standardModel.setItem(1,0,&item_cohesive);
            standardModel.setItem(2,0,&item_structure);
            //        standardModel->setItem(3,0,item_mesh);
            standardModel.setItem(4,0,&item_load);
            standardModel.setItem(5,0,&item_analysis);

            ui->treeView->setModel(&standardModel);
            ui->treeView->expandAll();

            file.close();
        }
    }

}

/* run MIDAS */
void MainWindow::runFESolver()
{
    QString inputDefaultFilePath = QDir::currentPath() +"/input.dat";

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Input File"), "",
            tr("Input File (*.dat);;All Files (*)"));
    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        if ( fileName != inputDefaultFilePath )
        {/* different input file from the existing input file is sellected*/
            /* remove the old input file
             * copy selected file to the default input file */
            QFile::remove(inputDefaultFilePath);
            QFile::copy(fileName, inputDefaultFilePath);
        }
        else
        {/* the same as existing is selected */
            /* do nothong */
        }

        /* check if the input file exists*/
        if ( !QFileInfo::exists(inputDefaultFilePath) )
        {
            QMessageBox::warning(this, " ", "No input file is found.");
            return;
        }
        else
        {
            QProcess *process = new QProcess(this);
            QString runFilePath = QDir::currentPath() + "/FESolver";
            /* the program waits until it runs */
            QProcess::execute(runFilePath);
//            process->start(runFilePath);

            if ( process->state() == QProcess::NotRunning )
            {
                QMessageBox::information(this, " ", "The simulation is done.");
            }
        }
    }
}

/* write input file */
void MainWindow::writeInputfile()
{

    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Write Input File"), "",
           tr("InputFile (*.dat);;All Files (*)"));

    if (fileName.isEmpty())
    {
            return;
    }
    else
    {
        QFile mFile(fileName);
        if (!mFile.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::information(this, tr("Unable to open file"), mFile.errorString());
            return;
        }
        else if(item_constitutive.rowCount()==0)
        {
            QMessageBox::warning(this, " ", "No material model is defined.");
            return;
        }
        else if(item_cohesive.rowCount()==0)
        {
            QMessageBox::warning(this, " ", "No interface model is defined.");
            return;
        }
        else if(item_structure.rowCount()==0)
        {
            QMessageBox::warning(this, " ", "No layer is defined.");
            return;
        }
        else if(item_mesh.rowCount()==0)
        {
            QMessageBox::warning(this, " ", "No mesh data is defined.");
            return;
        }
        else if(item_load.rowCount()==0)
        {
            QMessageBox::warning(this, " ", "No load configuration is defined.");
            return;
        }
        else if(item_analysis.rowCount()==0)
        {
            QMessageBox::warning(this, " ", "No analysis time is defined.");
            return;
        }
        else
        {
            QTextStream out(&mFile);

            /* some priliminary data extraction ----------------------------------*/
            meshSubLayer mesh = meshSubLayer( item_mesh.child(0,0)->data(Qt::UserRole + 4).value<modelMesh>().coo_global,
                                              item_mesh.child(0,0)->data(Qt::UserRole + 4).value<modelMesh>().con_bulk,
                                              item_mesh.child(0,0)->data(Qt::UserRole + 4).value<modelMesh>().con_coh);

            /* section 1 ---------------------------------------------------------*/
            int JNEL    = Size(mesh.con,1)+1; /*Max No of EL*/
            int JNNODE  = Size(mesh.coo,1)+1; /*Max No of Node*/
            int JNDOF   = 2 * JNNODE; /*Max No of DOF*/
            int JBANDW  = JNDOF; /*Max No of BANDW*/
            int JNINT   = Size(mesh.coh,1)+1; /*Max no. of interface el*/
            int JNIPNT  = 3;    /* intgration point */
            int JNIMOD  = 10;    /* number of interface models */
            int JPRONY  = 20;   /*Max No of Prony*/
            int JNUMVIS = 10;    /* number of viscoelstic models*/
            int JTBLK   = 10;    /* number of time block */
            int NELNODE = 3;    /* number of node per el */
            int JDIM    = 4;    /* 4 for 2D */
            int JDINC   = 10000; /* Max No of BC disp icriment for DOF */

            out << JNEL << " " << JNNODE << " " << JNDOF << " " << JBANDW << " " << JNINT << " " << JNIPNT << " "
                << JNIMOD << " " << JPRONY << " " << JNUMVIS << " " << JTBLK << " " << NELNODE << " " << JDIM << " " << JDINC;
            out << "\n";
            out << "\n";
            /* section 2 ---------------------------------------------------------*/
            int NDIM = 2; /*No. of dimension*/
            int NN = Size(mesh.coo,1); /*No. of nodes*/
            int NEL = Size(mesh.con,1); /* No. of bulk el */
            /* calculate NF */
            QList<int> NumOfNodePerLoad;
            for(int i=0; i<item_load.rowCount(); i=i+1)
            {/* loop over loadings*/
                modelLoading theLoading = item_load.child(i,0)->data(Qt::UserRole + 5).value<modelLoading>();
                double leftCoo = theLoading.tireCentCoo - theLoading.tireWidth/2;
                double rightCoo = theLoading.tireCentCoo + theLoading.tireWidth/2;

                Matrix topNodes = mesh.getSideNodes("top");
                int counter=0;
                for(int j=1; j <= Size(topNodes,1); j=j+1)
                {
                    if( mesh.coo( static_cast<int>(topNodes(j,1)), 1) >= leftCoo &&
                        mesh.coo( static_cast<int>(topNodes(j,1)), 1) <= rightCoo )
                    {
                        counter = counter + 1;
                    }
                }
                NumOfNodePerLoad << counter;
            }
            int counter = 0;
            for (int i=0; i < NumOfNodePerLoad.size(); i=i+1)
            {
                counter = counter + NumOfNodePerLoad[i];
            }
            int NF = counter; /*NUMBER OF NODES WITH EXTERNALLY APPLIED LOADS*/

            int NDBC = Size(mesh.getSideNodes("left"),1)-1 + /*NUMBER OF DISP. BOUNDARY CONDITIONS- DOF*/
                    Size(mesh.getSideNodes("right"),1)-1 +
                    2*Size(mesh.getSideNodes("bottom"),1); /*removing the first node on left and right edges
                                                        since it is already in the bottom edge */;
            int NNPEREL=3; /* No. of node per el*/
            int NLCUR = 0; /*NUMBER OF LOAD CURVES*/
            int NANIM = 1; /*Animation output*/

            out << NDIM << " " << NN << " " << NEL << " " << NF << " " << NDBC << " " << NNPEREL << " " << NLCUR << " " << NANIM;
            out << "\n";
            out << "\n";
            /* section 3 ---------------------------------------------------------*/
            modelTime theSimTime = item_analysis.child(0,0)->data(Qt::UserRole + 6).value<modelTime>();

            double TotalTime = theSimTime.totalTime;
            double TimeIncr = theSimTime.timeIncrement;
            if(std::abs(TotalTime-0)<=eps || std::abs(TimeIncr-0)<=eps )
            {/*  */
                QMessageBox::warning(this, " ", "Please inter valid time.");
            }

            int NSTE   = qFloor(TotalTime/TimeIncr); /*NSTE= NUMBER OF SOLUTION STEPS*/
            int IINT   = Size(mesh.coh,1); /*EQ. ZERO UNLESS USING INTERFACE ELEMENTS*/
            int ITYPE  = 2; /*end planestress-1, planestrain-2*/
            int IVARI  = 1; /*NUMBER OF TIME BLOCKS TO BE INPUT*/
            int NOMAT  = item_constitutive.rowCount(); /*NUMBER OF MATERIAL MODELS USED*/

            modelLoading theLoading = item_load.child(0,0)->data(Qt::UserRole + 5).value<modelLoading>(); /*since we can only define one type of loading, the first loading is choosen*/
            double HERTZ = 1/theLoading.s_cycleDuration; /* cyclic load freq*/
            int ICTYPE = 0.0; /*FLAG FOR CYCLIC BC*/
            if(theLoading.loadingType == "Sine")
            {
                HERTZ  = 1/theLoading.s_cycleDuration;
                ICTYPE = 0;
            }
            else if(theLoading.loadingType == "Sine-Pulse")
            {
                HERTZ  = 1.0; /*inthis case it wont be used*/
                ICTYPE = 2;
            }
            out << NSTE << " " << IINT << " " << ITYPE << " " << IVARI << " " << NOMAT << " " << HERTZ << " " << ICTYPE;
            out << "\n";
            out << "\n";
            /* section 4 ---------------------------------------------------------*/
            double RTOL= 0.005;
            int IPTYPE = 1;
            int IPRI   = 1;
            int ISREF  = 1;
            int IEQUIT = 1;
            int ITEMAX = 25;

            out << RTOL << " " << IPTYPE << " " << IPRI << " " << ISREF << " " << IEQUIT << " " << ITEMAX;
            out << "\n";
            out << "\n";
            /* section 5 ---------------------------------------------------------*/
            /* this part is set for only when IVARI = 1 */
            if (IVARI==0)
            {
                //        double TFAC(1) =1.0; /*MULTIPLICATIVE FACTOR FOR ALL INPUTS DURING ITH TIMEBLOCK*/
                //        double TIMEB(1) =1000000.0;
            }
            else
            {
                double TIMEB=TotalTime;
                double TFAC=1;
                double DTIM=TimeIncr;
                for (int I=1; I<=IVARI; I=I+1)
                {
                    out << TIMEB << " " << TFAC << " " << DTIM;
                }
                out << "\n";
            }
            out << "\n";
            /* section 6 ---------------------------------------------------------*/
            for (int II=1; II<=Size(mesh.coo,1); II=II+1)
            {
                out << II << " " << mesh.coo(II,1) << " " << mesh.coo(II,2);
                out << "\n";
            }
            out << "\n";
            /* section 7 ---------------------------------------------------------*/
            if (NNPEREL==3)
            {
                // int NINTPT=1;
                for (int II=1; II<=Size(mesh.con,1); II=II+1)
                {
                    out << II << " "
                        << mesh.con(II,1) << " " << mesh.con(II,2) << " " << mesh.con(II,3) << " " << mesh.con(II,4) << " " << mesh.con(II,5) << " " << 0.0;
                    out << "\n";
                }
            }
            out << "\n";
            /* section 8 ---------------------------------------------------------*/
            int NVARI = IVARI;
            if( IVARI == 0 )
            {
                NVARI = 1;
            }

            int NDISP = NDBC;
            out << NDISP;
            out << "\n";
            /* section 9 ---------------------------------------------------------*/
            Matrix leftNodes = Matrix(Size(mesh.getSideNodes("left"),1)-1,1);
            Matrix rightNodes = Matrix(Size(mesh.getSideNodes("right"),1)-1,1);
            Matrix bottomNodes = mesh.getSideNodes("bottom");

            leftNodes = mesh.getSideNodes("left").partial(2, Size(mesh.getSideNodes("left"),1), 1, 1);
            rightNodes = mesh.getSideNodes("right").partial(2, Size(mesh.getSideNodes("right"),1), 1, 1);

            Matrix NDOFaux1 = vertCat(2*leftNodes-1, 2*rightNodes-1);
            Matrix NDOFaux2 = vertCat(NDOFaux1, 2*bottomNodes-1);
            Matrix NDOF = vertCat(NDOFaux2, 2*bottomNodes);

            Matrix DINC = Zeros(Size(NDOF,1),1);
            //    DINC = DINC * IncrDisp;

            if (NVARI==1)
            {
                /* write NDOF */
                for (int i = 1; i<=Size(NDOF,1); i = i+1)
                {
                    out << NDOF(i,1) << " ";
                    if((i-qFloor(i/10)*10) == 0){out << "\n";}
                }
                out << "\n";

                /* write DINC */
                for (int i = 1; i<=Size(DINC,1); i = i+1)
                {
                    out << DINC(i,1) << " ";
                    if((i-qFloor(i/4)*4) == 0){out << "\n";}
                }
                out << "\n";
            }
            else
            {
                for( int J= 1; J<=NVARI; J = J+1)
                {
                    //            fprintf(InputFileID,'%7d %7d %7d %7d %7d %7d %7d %7d %7d %7d\r\n',...
                    //                NDOF);
                    //            %NDOF(1:NDISP(J)));  1005 FORMAT(10I8)

                    //            DINC = DINC * IncrDisp;% apply total disp to DOF
                    //            fprintf(InputFileID,'%15.7f %15.7f %15.7f %15.7f\r\n',...
                    //                                 DINC);
                }
            }
            out << "\n";
            /* section 10 --------------------------------------------------------*/
            /* define loading curve*/

            /* find loading nodes */
            Matrix ICURVE = Matrix(NF,1);
            Matrix FA1 = Matrix(NF,1);
            Matrix FA2 = Matrix(NF,1);
            Matrix INODE = Matrix(NF,1);
            counter = 1;
            for(int i=0; i<item_load.rowCount(); i=i+1)
            {/* loop over loadings*/
                modelLoading theLoading = item_load.child(i,0)->data(Qt::UserRole + 5).value<modelLoading>();
                double nodalLoadAmp = (theLoading.amplitude * theLoading.tireWidth) / NumOfNodePerLoad[i];
                double leftCoo = theLoading.tireCentCoo - theLoading.tireWidth/2;
                double rightCoo = theLoading.tireCentCoo + theLoading.tireWidth/2;

                Matrix topNodes = mesh.getSideNodes("top");
                for(int j=1; j <= Size(topNodes,1); j=j+1)
                {
                    if(mesh.coo(static_cast<int>(topNodes(j,1)),1) >= leftCoo &&
                       mesh.coo(static_cast<int>(topNodes(j,1)),1) <= rightCoo)
                    {
                        ICURVE(counter,1) = 1; /*1: sin-pulse*/
                        FA1(counter,1) = 0;
                        FA2(counter,1) = -1 * nodalLoadAmp;
                        INODE(counter, 1) = topNodes(j,1);
                        counter = counter + 1;
                    }
                }
            }

            NF = Size(INODE,1);
            /* FA1 - FORCE COMPONENT IN X  DIRECTION */
            /* FA2 - FORCE COMPONENT IN Y  DIRECTION */

            if (NF != 0)
            {
                for (int I=1; I <= NF; I = I+1)
                {
                    out << INODE(I,1) << " " << ICURVE(I,1) << " " << FA1(I,1)  << " " << FA2(I,1);
                    out << "\n";
                }

                if (ICTYPE == 2)
                {
                    out << item_load.child(0,0)->data(Qt::UserRole + 5).value<modelLoading>().sp_cycleDuration  << " " <<
                           item_load.child(0,0)->data(Qt::UserRole + 5).value<modelLoading>().sp_pulseDuration;
                    out << "\n";
                }
            }
            out << "\n";
            /* section 11 --------------------------------------------------------*/
            int MODNUM1 = 0;
            int MODNUM2 = 0;
            for(int i=0; i<item_constitutive.rowCount(); i=i+1)
            {/* loop over constitutives*/
                modelConstitutive theConstitutive = item_constitutive.child(i,0)->data(Qt::UserRole + 1).value<modelConstitutive>();

                if(theConstitutive.matType == 1 && MODNUM1 < theConstitutive.matSet)
                {
                    MODNUM1 = theConstitutive.matSet;
                }
                else if(theConstitutive.matType == 2 && MODNUM2 < theConstitutive.matSet)
                {
                    MODNUM2 = theConstitutive.matSet;
                }
            }

            out << MODNUM1 << " " << MODNUM2;
            out << "\n";
            out << "\n";

            /*elastic*/
            for(int i=0; i<item_constitutive.rowCount(); i=i+1)
            {/* loop over constitutives*/
                modelConstitutive theConstitutive = item_constitutive.child(i,0)->data(Qt::UserRole + 1).value<modelConstitutive>();

                if(theConstitutive.matType == 1)
                {
                    int MSETI = theConstitutive.matSet;
                    double EE    = theConstitutive.elElasticModulus;
                    double VNU   = theConstitutive.elPoissonRatio;
                    double Y     = std::pow(10,90);
                    double ALPHAT= std::pow(10,-4);

                    out << MSETI << " " << EE << " " << VNU << " " << Y << " " << ALPHAT;
                    out << "\n";
                    out << "\n";
                }
            }

            /*viscoelastic*/
            if (MODNUM2 != 0)
            {
                int IVTYPE = 0; /*???????????????????????????*/
                double DTIME = 0.0001; /*???????????????????????????*/

                out << IVTYPE << " " << DTIME;
                out << "\n";

                //int NMOD = MODNUM2;

                for(int i=0; i<item_constitutive.rowCount(); i=i+1)
                {/* loop over constitutives*/
                    modelConstitutive theConstitutive = item_constitutive.child(i,0)->data(Qt::UserRole + 1).value<modelConstitutive>();

                    if(theConstitutive.matType == 2)
                    {
                        int MSETII  = theConstitutive.matSet; /*VISCOELASTIC MODEL NUMBER*/
                        double NT11 = theConstitutive.veRelaxModuPS.size(); /*NUMBER OF PRONY TERMS IN CLii*/
                        double NT12 = theConstitutive.veRelaxModuPS.size();
                        double NT22 = theConstitutive.veRelaxModuPS.size();
                        double NT23 = theConstitutive.veRelaxModuPS.size();
                        double NT44 = theConstitutive.veRelaxModuPS.size();
                        double NT66 = theConstitutive.veRelaxModuPS.size();

                        out << MSETII << " " << NT11 << " " << NT12 << " " << NT22 << " " << NT23 << " " << NT44 << " " << NT66;
                        out << "\n";

                        double NU = theConstitutive.vePoissonRatio;
                        double E  = theConstitutive.veRelaxModuInf;

                        double MIU      = E / (2*(1+NU));
                        double LAMBDA  = (E*NU) / ((1+NU)*(1-2*NU));

                        double CLINF11 = LAMBDA+2*MIU; /*CL Infinity*/
                        double CLINF12 = LAMBDA;
                        double CLINF22 = LAMBDA+2*MIU;
                        double CLINF23 = LAMBDA;
                        double CLINF44 = 2*MIU;
                        double CLINF66 = 2*MIU;

                        out << CLINF11 << " " << CLINF12 << " " << CLINF22 << " " << CLINF23 << " " << CLINF44 << " " << CLINF66;
                        out << "\n";


                        Matrix CL11 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix CL12 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix CL22 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix CL23 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix CL44 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix CL66 = Matrix(theConstitutive.veRelaxModuPS.size(),1);

                        Matrix ETA11 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix ETA12 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix ETA22 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix ETA23 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix ETA44 = Matrix(theConstitutive.veRelaxModuPS.size(),1);
                        Matrix ETA66 = Matrix(theConstitutive.veRelaxModuPS.size(),1);

                        for( int PP=1; PP<= theConstitutive.veRelaxModuPS.size(); PP = PP+1)
                        {
                            double NU = theConstitutive.vePoissonRatio;
                            double E  = theConstitutive.veRelaxModuPS[PP-1];

                            double MIU      = E / (2*(1+NU));
                            double LAMBDA  = (E*NU) / ((1+NU)*(1-2*NU));

                            CL11(PP,1) = LAMBDA+2*MIU;
                            CL12(PP,1) = LAMBDA;
                            CL22(PP,1) = LAMBDA+2*MIU;
                            CL23(PP,1) = LAMBDA;
                            CL44(PP,1) = 2*MIU;
                            CL66(PP,1) = 2*MIU;

                            ETA11(PP,1) = CL11(PP,1) * theConstitutive.veRelaxTimePS[PP-1];
                            ETA12(PP,1) = CL12(PP,1) * theConstitutive.veRelaxTimePS[PP-1];
                            ETA22(PP,1) = CL22(PP,1) * theConstitutive.veRelaxTimePS[PP-1];
                            ETA23(PP,1) = CL23(PP,1) * theConstitutive.veRelaxTimePS[PP-1];
                            ETA44(PP,1) = CL44(PP,1) * theConstitutive.veRelaxTimePS[PP-1];
                            ETA66(PP,1) = CL66(PP,1) * theConstitutive.veRelaxTimePS[PP-1];
                        }

                        /* 11 */
                        for (int i = 1; i<=Size(CL11,1); i = i+1)
                        {
                            out << CL11(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(CL11,1)-qFloor(Size(CL11,1)/4)*4) != 0){out << "\n";}

                        for (int i = 1; i<=Size(ETA11,1); i = i+1)
                        {
                            out << ETA11(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(ETA11,1)-qFloor(Size(ETA11,1)/4)*4) != 0){out << "\n";}

                        /*12*/
                        for (int i = 1; i<=Size(CL12,1); i = i+1)
                        {
                            out << CL12(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(CL12,1)-qFloor(Size(CL12,1)/4)*4) != 0){out << "\n";}

                        for (int i = 1; i<=Size(ETA12,1); i = i+1)
                        {
                            out << ETA12(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(ETA12,1)-qFloor(Size(ETA12,1)/4)*4) != 0){out << "\n";}

                        /* 22 */
                        for (int i = 1; i<=Size(CL22,1); i = i+1)
                        {
                            out << CL22(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(CL22,1)-qFloor(Size(CL22,1)/4)*4) != 0){out << "\n";}

                        for (int i = 1; i<=Size(ETA22,1); i = i+1)
                        {
                            out << ETA22(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(ETA22,1)-qFloor(Size(ETA22,1)/4)*4) != 0){out << "\n";}

                        /* 23 */
                        for (int i = 1; i<=Size(CL23,1); i = i+1)
                        {
                            out << CL23(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(CL23,1)-qFloor(Size(CL23,1)/4)*4) != 0){out << "\n";}

                        for (int i = 1; i<=Size(ETA23,1); i = i+1)
                        {
                            out << ETA23(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(ETA23,1)-qFloor(Size(ETA23,1)/4)*4) != 0){out << "\n";}

                        /* 44 */
                        for (int i = 1; i<=Size(CL44,1); i = i+1)
                        {
                            out << CL44(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(CL44,1)-qFloor(Size(CL44,1)/4)*4) != 0){out << "\n";}

                        for (int i = 1; i<=Size(ETA44,1); i = i+1)
                        {
                            out << ETA44(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(ETA44,1)-qFloor(Size(ETA44,1)/4)*4) != 0){out << "\n";}

                        /* 66 */
                        for (int i = 1; i<=Size(CL66,1); i = i+1)
                        {
                            out << CL66(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(CL66,1)-qFloor(Size(CL66,1)/4)*4) != 0){out << "\n";}

                        for (int i = 1; i<=Size(ETA66,1); i = i+1)
                        {
                            out << ETA66(i,1) << " ";
                            if((i-qFloor(i/4)*4) == 0){out << "\n";}
                        }
                        if((Size(ETA66,1)-qFloor(Size(ETA66,1)/4)*4) != 0){out << "\n";}

                    }
                }

            }
            /* section 12 --------------------------------------------------------*/
            /*NINEL - NO. OF INTERFACE ELEMENTS*/
            /*NINTG - NO. OF INTERFACE MATERIAL GROUPS*/
            /*NPRONY - NO. OF TERMS IN PRONY SERIES*/
            /*IDAMAGE -  FLAG FOR DAMAGE EVOLUTION LAW =
                   0 MEANS POWER LAW DAMAGE MODEL
                   1 MEANS PROBABILISTIC DAMAGE MODEL
                   2 Gaussian function */

            if (IINT !=0 )
            {

                int NINEL= Size(mesh.coh,1);
                int NINTG= item_cohesive.rowCount();

                out << NINEL << " " << NINTG;
                out << "\n";
                out << "\n";

                for (int II = 0; II<NINTG; II=II+1)
                {
                    modelCohesive theCohesive = item_cohesive.child(II,0)->data(Qt::UserRole + 2).value<modelCohesive>();

                    int IDAMAGE = 0;
                    if (theCohesive.bondingDamageIndex==1) {IDAMAGE = 0;} /*Power law*/
                    else if (theCohesive.bondingDamageIndex==2) {IDAMAGE = 2;} /*Gaussian Function*/

                    out << IDAMAGE;
                    out << "\n";
                    if( IDAMAGE==0 )
                    {

                        double SigmaN = theCohesive.czSigmaN;
                        double DeltaN = theCohesive.czDeltaN;
                        double SigmaT = theCohesive.czSigmaT;
                        double DeltaT = theCohesive.czDeltaT;

                        out << SigmaN << " " << DeltaN << " " << SigmaT << " " << DeltaT;
                        out << "\n";

                        double PLc = theCohesive.czDamagePowerFunC;
                        double PLn = theCohesive.czDamagePowerFunN;
                        double PLm = theCohesive.czDamagePowerFunM;

                        out << PLc << " " << PLn << " " << PLm;
                        out << "\n";
                    }
                    else if( IDAMAGE==2)
                    {
                        double SigmaN = theCohesive.czSigmaN;
                        double DeltaN = theCohesive.czDeltaN;
                        double SigmaT = theCohesive.czSigmaT;
                        double DeltaT = theCohesive.czDeltaT;

                        out << SigmaN << " " << DeltaN << " " << SigmaT << " " << DeltaT;
                        out << "\n";

                        double ConA = theCohesive.czDamageGaussFunA;
                        double ConM = theCohesive.czDamageGaussFunM;
                        double ConLambdabar = theCohesive.czDamageGaussFunL;
                        double ConDelta = theCohesive.czDamageGaussFunD;

                        out << ConA << " " << ConM << " " << ConLambdabar << " " << ConDelta;
                        out << "\n";
                    }

                    int NPRONY = theCohesive.czVERelaxModuPS.size();
                    double ECINF = theCohesive.czVERelaxModuInf;

                    out << NPRONY << " " << ECINF;
                    out << "\n";

                    Matrix EC = Matrix(NPRONY,1);
                    Matrix ETAC = Matrix(NPRONY,1);
                    for (int PP=1; PP <= NPRONY; PP=PP+1)
                    {
                        EC(PP,1)   = theCohesive.czVERelaxModuPS[PP-1];
                        ETAC(PP,1) = EC(PP,1) * theCohesive.czVERelaxTimePS[PP-1];

                        out << EC(PP,1) << " " << ETAC(PP,1);
                        out << "\n";
                    }
                }
                out << "\n";
                /* section 13 --------------------------------------------------------*/

                for(int I=1; I<=NINEL; I=I+2)
                {
                    int NINT1 = static_cast<int>(mesh.coh(I,1));
                    int NINT2 = static_cast<int>(mesh.coh(I,2));

                    int NINT3 = static_cast<int>(mesh.coh(I+1,1));
                    int NINT4 = static_cast<int>(mesh.coh(I+1,2));

                    int IGR = static_cast<int>(mesh.coh(I,3));

                    double X1 = mesh.coo(NINT1,1);
                    double Y1 = mesh.coo(NINT1,2);

                    double X3 = mesh.coo(NINT3,1);
                    double Y3 = mesh.coo(NINT3,2);

                    double WIDTH = std::sqrt( std::pow((X1-X3),2) + std::pow((Y1-Y3),2) );

                    double PHIAV;
                    if ( std::abs(X3-X1) < eps)
                    {
                        PHIAV = 2*std::atan(1);
                    }
                    else
                    {
                        PHIAV= std::atan( (Y3-Y1)/(X3-X1) );
                    }

                    out << NINT1 << " " << NINT2 << " " << IGR << " " << WIDTH << " " << PHIAV;
                    out << "\n";
                    out << NINT3 << " " << NINT4 << " " << IGR << " " << WIDTH << " " << PHIAV;
                    out << "\n";
                }
            }

            mFile.flush();
            mFile.close();
        }
    }
}

/* plot the model */
void MainWindow::visualizeModel()
{/* this part open a new window to plot the model */
    /* model approach */
    //        Dialog dialogPlotMesh;
    //        dialogPlotMesh.setModal(true);
    //        dialogPlotMesh.exec();

    /* non-model approach */
//    Dialog* dialogPlotMesh  = new Dialog(this);
//    Dialog* dialogPlotMesh = new Dialog(this);

//    dialogPlotMesh->theModel = &standardModel;
    dialogPlotMesh.setModel(&standardModel);
    dialogPlotMesh.plotModel();

    dialogPlotMesh.show();
}

// ============================================================================
//
// ============================================================================
void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QStandardItem* clickedChild = standardModel.itemFromIndex( index );
    int clickedChild_row = clickedChild->row();
    QStandardItem* parentClickedChild = clickedChild->parent();

    if (parentClickedChild != nullptr)
    {/* not parent item is selected */

        int parentClickedChild_row = parentClickedChild->row();
        ui->tabWidget->setCurrentIndex(parentClickedChild_row);

        /* update confirm button and comboboxes */
        on_tabWidget_tabBarClicked(parentClickedChild_row);

        if (parentClickedChild_row == 0)
        {/* material */
            modelConstitutive theMat = item_constitutive.child(clickedChild_row,0)->data(Qt::UserRole + 1).value<modelConstitutive>();

            ui->lineEdit->setText(theMat.label);

            ui->comboBox->setCurrentIndex(theMat.matType);

            ui->lineEdit_2->setText(QString::number(theMat.elElasticModulus));
            ui->lineEdit_3->setText(QString::number(theMat.elPoissonRatio));

            initializeQTable(ui->tableWidget);
            ui->tableWidget->item(0,0)->setText(QString::number(theMat.veRelaxModuInf));

            for(int i=1; i<=theMat.veRelaxModuPS.size(); i=i+1)
            {
                ui->tableWidget->item(i, 0)->setText(QString::number(theMat.veRelaxModuPS[i-1]));
                ui->tableWidget->item(i, 1)->setText(QString::number(theMat.veRelaxTimePS[i-1]));
            }

            ui->lineEdit_5->setText(QString::number(theMat.vePoissonRatio));

        }
        else if (parentClickedChild_row == 1)
        {/* cohesive */
            modelCohesive theCoh = item_cohesive.child(clickedChild_row,0)->data(Qt::UserRole + 2).value<modelCohesive>();

            ui->lineEdit_4->setText(theCoh.label);

            ui->comboBox_2->setCurrentIndex(theCoh.cohType);
            ui->stackedWidget_2->setCurrentIndex(theCoh.cohType);

            initializeQTable(ui->tableWidget_2);
            ui->tableWidget_2->item(0,0)->setText(QString::number(theCoh.czVERelaxModuInf));

            for(int i=1; i<=theCoh.czVERelaxModuPS.size(); i=i+1)
            {
                ui->tableWidget_2->item(i, 0)->setText(QString::number(theCoh.czVERelaxModuPS[i-1]));
                ui->tableWidget_2->item(i, 1)->setText(QString::number(theCoh.czVERelaxTimePS[i-1]));
            }

            ui->lineEdit_13->setText(QString::number(theCoh.czDeltaN));
            ui->lineEdit_14->setText(QString::number(theCoh.czDeltaT));
            ui->lineEdit_15->setText(QString::number(theCoh.czSigmaN));
            ui->lineEdit_16->setText(QString::number(theCoh.czSigmaT));

            ui->comboBox_3->setCurrentIndex(theCoh.bondingDamageIndex);
            ui->stackedWidget_3->setCurrentIndex(theCoh.bondingDamageIndex);

            ui->lineEdit_6->setText(QString::number(theCoh.czDamagePowerFunC));
            ui->lineEdit_7->setText(QString::number(theCoh.czDamagePowerFunN));
            ui->lineEdit_8->setText(QString::number(theCoh.czDamagePowerFunM));

            ui->lineEdit_9->setText(QString::number(theCoh.czDamageGaussFunA));
            ui->lineEdit_10->setText(QString::number(theCoh.czDamageGaussFunM));
            ui->lineEdit_11->setText(QString::number(theCoh.czDamageGaussFunL));
            ui->lineEdit_12->setText(QString::number(theCoh.czDamageGaussFunD));

        }
        else if (parentClickedChild_row == 2)
        {/* layer */
            modelLayer theLayer = item_structure.child(clickedChild_row,0)->data(Qt::UserRole + 3).value<modelLayer>();

            ui->lineEdit_17->setText(theLayer.label);
            ui->lineEdit_18->setText(QString::number(theLayer.thickness));
            ui->lineEdit_19->setText(QString::number(theLayer.width));

            ui->comboBox_4->setEnabled(true);
            ui->comboBox_4->setCurrentText(theLayer.constitutiveModel.label);

            ui->comboBox_7->setEnabled(true);
            ui->comboBox_7->setCurrentText(theLayer.bottomCohModel.label);

            ui->comboBox_8->setEnabled(true);
            ui->comboBox_8->setCurrentText(theLayer.midlineCohModel.label);

        }
        else if (parentClickedChild_row == 3)
        {/* mesh */
            modelMesh theMesh = item_mesh.child(clickedChild_row,0)->data(Qt::UserRole + 4).value<modelMesh>();

            ui->lineEdit_20->setText(QString::number(theMesh.meshSize));
            ui->lineEdit_31->setText(QString::number(theMesh.numOfNodes));
            ui->lineEdit_32->setText(QString::number(theMesh.numOfBulkEl));
            ui->lineEdit_33->setText(QString::number(theMesh.numOfIntEl));

        }
        else if (parentClickedChild_row == 4)
        {/* load */
            modelLoading theLoad = item_load.child(clickedChild_row,0)->data(Qt::UserRole + 5).value<modelLoading>();

            ui->lineEdit_24->setText(theLoad.label);
            ui->lineEdit_28->setText(QString::number(theLoad.tireCentCoo));
            ui->lineEdit_27->setText(QString::number(theLoad.tireWidth));

            if (theLoad.loadingType == "Sine")
            {
                ui->stackedWidget_4->setEnabled(true);
                ui->stackedWidget_4->setCurrentIndex(2);
                ui->comboBox_9->setCurrentIndex(2);

                ui->lineEdit_29->setText(QString::number(theLoad.amplitude));
                ui->lineEdit_30->setText(QString::number(theLoad.s_cycleDuration));
            }
            else if (theLoad.loadingType == "Sine-Pulse")
            {
                ui->stackedWidget_4->setEnabled(true);
                ui->stackedWidget_4->setCurrentIndex(1);
                ui->comboBox_9->setCurrentIndex(1);

                ui->lineEdit_21->setText(QString::number(theLoad.amplitude));
                ui->lineEdit_22->setText(QString::number(theLoad.sp_pulseDuration));
                ui->lineEdit_23->setText(QString::number(theLoad.sp_cycleDuration));
            }
        }
        else if (parentClickedChild_row == 5)
        {/* time */
            modelTime theTime = item_analysis.child(clickedChild_row,0)->data(Qt::UserRole + 6).value<modelTime>();

            ui->lineEdit_25->setText(QString::number(theTime.totalTime));
            ui->lineEdit_26->setText(QString::number(theTime.timeIncrement));
        }
    }
}

// ============================================================================
//
// ============================================================================
/* read from table - one column at a time */
QList<double> MainWindow::readFromTable(QTableWidget *table, int startRow, int columnIndex)
{
    /* columnIndex = 0 is first column */

    int numOfrows = 0;
    /* find num of rows which are filled */
    for(int i = startRow; i< table->rowCount(); i = i + 1)
    {
        QTableWidgetItem *a = table->item(i,0);
        QString aaa = a->text();

        bool flagNul_0 = table->item(i, 0)->text().isEmpty();

        if( flagNul_0 )
        {
            break;
        }
        else
        {
            numOfrows = numOfrows + 1;
        }
    }

    QList<double> tableData;
    /* read table data */
    for(int i = startRow; i <= numOfrows; i = i + 1)
    {
        tableData << table->item(i, columnIndex)->text().toDouble();
    }

    return tableData;
}

/* check for duplicated lable */
int MainWindow::isStrChildMember(QStandardItem *item, QString str)
{
    int index = -1;
    if(item->hasChildren())
    {
        for(int i = 0; i < item->rowCount(); i = i +1)
        {
            if(item->child(i,0)->text() == str)
            {
                index = i;
            }
        }
    }
    return index;
}

/* arithmetic progression*/
Matrix MainWindow::progression_arithmetic(double progStart, double progEnd, double progDiff)
{ /* make a arithmetic progression */

    int numOfmembers;
    double nOM = (progEnd - progStart)/ progDiff;
    if (qFabs(nOM-qFloor(nOM)) < qFabs(nOM-qCeil(nOM)))
    {
        numOfmembers = qFloor(nOM);
    }
    else if (qFabs(nOM-qFloor(nOM)) > qFabs(nOM-qCeil(nOM)))
    {
        numOfmembers = qCeil(nOM);
    }
    else
    {
        numOfmembers = qFloor(nOM);
    }
    numOfmembers = numOfmembers +1;

    // make a arithmetic progression
    // the last increment might be bigger than others
    Matrix progSeries = Matrix(numOfmembers,1);

    int counter = 1;

    for (double loc = progStart; loc < progEnd; loc = loc + progDiff)
    {
        progSeries(counter,1) = loc;
        counter = counter + 1;
    }
    progSeries(numOfmembers,1) = progEnd;

    return progSeries;
}

/* combine two marices */
Matrix MainWindow::placeBinA(Matrix A, Matrix B, int m, int n)
{
    /* C = place B in A starting at (m,n) */
    for(int i=1; i<= Size(B,1); i = i+1)
    {
        for(int j=1; j<= Size(B,2); j = j+1)
        {
            A((m-1)+i,(n-1)+j) = B(i,j);
        }
    }
    return A;
}



