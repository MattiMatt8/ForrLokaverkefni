# Lokaverkefni Forritun C++
* ### Skjöl
    * #### Lokaverkefni.cpp
        * Hefur main function/keyrir forritið.
        * Nota Enum í valmyndinni.
    * #### LinkedList.h
        * Heldur utan um linked listann og öll function fyrir hann.
    * #### BookingSystem.h
        * Sér um booking object sem halda utan um booking id, reserved og capacity.  Heldur líka utan um function til þess að vinna við objectið.
    * #### BookingValmynd.h
        * Hefur valmyndina fyrir booking, þannig það þarf aðeins að vera eitt sett af kóða fyrir valmynd fyrir bus booking, ship og flight.
* ### Virkni Bókunarkerfisins
    * #### Röðun og skjalarvinnsla
        * Það er hægt að raða linked listanum efir ascending eða descending röð þegar valið er bus booking, ship og flight.
        * Hvert booking er með sitt eigið skjal til að halda um bókanir eins og buses.csv, ships.csv og flights.csv.  Þau eru default skjölin en það er líka hægt að velja custom skjal.  Þegar það er skrifað quit þá vistar það í skjalið áður en það fer aftur í aðal valmyndina.
    * #### Skipanir
        * ##### create [id][cap]
            * Búa til nýja bókun.
        * ##### delete [id]
            * Eyða bókun.
        * ##### deleteR [s_ID][l_ID]
            * Eyða mörgum bókunum frá og með s_ID bókuninni og til og með l_ID bókuninni.
        * ##### add [id][n]
            * Bæta við farþegum við bókun.
        * ##### cancel [id][n]
            * Eyða farþegum úr bókun.
        * ##### compare [id][id2]
            * Bera saman tvær bókanir miðað við hversu full þau eru prósentulega.  Notar operator föll til að bera saman bókanir.
        * ##### move [fromID][toID]
            * Færir jafn marga farþega og hægt er frá fromID bókuninni til toID bókuninni.
        * ##### quit
            * Vistar og fer aftur í aðal valmynd.