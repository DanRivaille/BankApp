#ifndef TYPES_DATA_H
#define TYPED_DATA_H

#include <stdbool.h>

#include "TDA-Map/Map.h"
#include "TDA-List/List.h"

#define MAX_CARACT 15
#define MAX_NAME 30
#define MAX_NOTICES 150

struct typeProfile{                 //guardara los perfiles tanto de los admins, como de los clientes
    char rut[MAX_CARACT + 1];           //rut unico del usuario
    char pass[MAX_CARACT + 1];          //contraseña asociada al rut
};

typedef struct typeProfile typeProfile;

struct typeNotice{                  //guardara la informacion de los avisos que tenga un cliente
    char notice[MAX_NOTICES + 1];       //guardara el aviso textual
    bool readed;                        //representara si el aviso a sido leido o no (true -> leido)
};

typedef struct typeNotice typeNotice;

struct Date{                        //registro para trabajar con las fechas
    int day;
    int month;
    int year;
};

typedef struct Date Date;

struct typeAddressee{                       //guardara la informacion de un destinatario
    char rut[MAX_CARACT + 1];                   //rut asociado
    char name[MAX_NAME + 1];                    //nombre asociado
    char account_number[MAX_CARACT + 1];        //numero de cuenta
    char account_type;                          //tipo de cuenta (cuenta rut o cuenta de ahorro)
    bool favorite;                              //si esta guardado como favorito guardara true, en caso contrario false
};

typedef struct typeAddressee typeAddressee;

struct typeTransaction{                     //guardara la informacion de una transaccion
    long int amount;                            //monto transferido, (si es + significa que recibio dinero, sino que se tranfirio)
    typeAddressee *associated_acount;           //informacion de la cuenta asociada
    Date *date;                                 //fecha de la transaccion
};

typedef struct typeTransaction typeTransaction;

struct typeAccount{                         //guardara la informacion de una cuenta
    unsigned long int balance;                  //saldo contable
    char account_number[MAX_CARACT + 1];        //numero de cuenta (si es cuenta rut, sera el rut sin digito verificador)
    char account_type;                          //tipo de cuenta (cuenta rut - cuenta de ahorro)
    Map *addressees;                            //mapa con los destinatarios guardados (tambien incluye los favoritos)
    List *transactions_history;                 //lista que guardara el historial de transacciones realizadas (ultimas 10)
};

typedef struct typeAccount typeAccount;

struct typeClient{                          //guardara la informacion de un cliente
    char rut[MAX_CARACT + 1];                   //rut asociado (sin digito verificador)
    char name[MAX_NAME + 1];                    //nombre ingresado por el cliente
    typeAccount *rut_account;                   //informacion de la cuenta rut (todos los clientes la tienen activa por defecto)
    typeAccount *saving_account;                //informacion de la cuenta ahorro (el cliente tiene que activarla)
    int notices;                                //cantidad de avisos del cliente
};

typedef struct typeClient typeClient;

#endif // TYPES_DATA_H
