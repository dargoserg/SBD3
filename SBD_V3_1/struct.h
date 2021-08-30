#ifndef STRUCT_H
#define STRUCT_H
#include <QString>
#include<myclasstablemodel.h>
struct structAddress
{
    QString settlement;
    QString street;
    QString house;
    QString building;
    QString apartment;
    QString districtName;
    QString districtId;
};

struct structRecord
{
    QString fam;
    QString name;
    QString otch;
    QString dateOfBirth;
    QString dateOfRecord;
    QString idSex;
    QString settlement;
    QString workPlace;
    QString dateOfAppeal;
    QString idWorkingPosition;
    QString idDistrict;
    QString street;
    QString house;
    QString building;
    QString apartment;
    QString idTypeOfSettlement;
    QString idSocialGroup;
    QString idPatientCategory;
    QString idDiagnosis;
    QString idLocationOfDiagnosis;
    QString idCircumstancesOfTheDiagnosis;
    QString dateOfDiagnosis;
    QString idMedic;
    QString medic;
    QString idLaboratoryConfirmation;
    QString laboratoryConfirmation;

    //INSERT INTO `mydb`.`izvesh` (`FAM`, `IMA`, `OTCH`, `VOZ`, `DATE_ZAP`, `POL`, `NPUNKT`, `MWORK`, `DATA_OB`, `KOD_DOL`, `KOD_RAION`, `ULISA`, `DOM`, `KOR`, `KV`, `GOR_SEL`,
    //`KOD_SOC`, `KOD_KAT`, `KOD_DIAG`, `KOD_MESTO`, `KOD_OBST`, `DATA_U`, `KOD_VRACH`, `VRACH`, `KOD_MESTO_TYPE`, `DATA_ZAP`, `KOD_LAB_POT`, `LAB_POT_RAS`, `IDIZV`) VALUES ('Тураев', 'Анатолий', 'Михайлович', '1924-12-31', '1994-12-01', '1', 'Саратов', 'не работает', '1994-11-22', '2', '3', 'Кутякова', '65', '', '63', '1', '14', '11', '77', '395', '2', '1994-11-22', '64', 'Буданов', '18', '2015-06-11 09:59:51', '14', '', '1000');

};
/*
struct structTableModel
{
    MyClassTableModel *medicList;
    MyClassTableModel *typeOfSettlementList;
};
*/
#endif // STRUCT_H
