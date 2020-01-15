#include <LiquidCrystal.h>

#define BUTON1 PC_5
#define BUTON2 PD_2
#define BUTON3 PD_3
#define BUTON4 PD_6
#define BUTON5 PD_7
#define RESET PF_4
#define BITIS PB_2
#define LEDY PA_7
#define LEDK PA_6
                      //RS,   E    , D4 , D5 , D6 ,    D7
   LiquidCrystal lcd(PB_0, PB_1, PB_4, PB_5, PB_6, PB_7);

    char m1[20];
    char m2[20];
    char m3[20];
    char m4[20];
    char e1[20];
    char e2[20];
    char e3[20];
    char e4[20];
    char e5[20];
   int length,i;
   int adets;
   float kasatop = 0;
   float para[3] = {0.25,0.50,1};
   float paraustu = 0;
   int ending;
   int control = 0;
   int moneycounts[3];
   int itemc[5][4];
   float bakiye=0;
   float harcananpara=0;
   float display = 0;
   float money1 = 0 , money2 = 0 , money3 = 0;
   float money11 = 0 , money22 = 0 , money33 = 0;
   int proc1 = 0 , proc2 = 0 , proc3 = 0 , proc4 = 0 , proc5 = 0;
   int proc11 = 0 , proc22 = 0 , proc33 = 0 , proc44 = 0 , proc55 = 0;
   float items[5][4];
   char UrunAd[5]={'Su','Cay','Kahve','Cikolata','Biskuvi'};
   char * moneycount[3];
   char * item[5][4];
   char text[]={'2','0',',','2','0',',','1','0','\n','1',',','s','u',',','3','0',',','5','0',' ','K','u','r','u','s','\n','2',',','c','a','y',',','2','0',',','1',' ','T','L','\n','3',',','k','a','h','v','e',',','1','5',',','1','.','5',' ','T','L','\n','4',',','c','i','k','o','l','a','t','a',',','5','0',',','1','.','7','5',' ','T','L','\n','5',',','b','i','s','k','u','v','i',',','1','0','0',',','2',' ','T','L',' ','\0'};

void textIsle(){
    length = strlen(text);

    sprintf(m4,"%d",moneycounts[0]);
    sprintf(m2,"%d",moneycounts[1]);
    sprintf(m3,"%d",moneycounts[2]);
    sprintf(e1,"%d",itemc[0][2]);
    sprintf(e2,"%d",itemc[1][2]);
    sprintf(e3,"%d",itemc[2][2]);

    sprintf(e4,"%d",itemc[3][2]);

    sprintf(e5,"%d",itemc[4][2]);

    text[0]=m4[0];
    text[1]=m4[1];
    text[2]=',';
    text[3]=m2[0];
    text[4]=m2[1];
    text[5]=',';
    text[6]=m3[0];
    text[7]=m3[1];
    text[8]=',';
    text[13]=' ';
    text[14]=e1[0];
    text[15]=e1[1];
    text[16]=',';
    text[31]=' ';
    text[32]=e2[0];
    text[33]=e2[1];
    text[34]=',';
    text[47]=' ';
    text[48]=e3[0];
    text[49]=e3[1];
    text[50]=',';
    text[68]=' ';
    text[69]=e4[0];
    text[70]=e4[1];
    text[71]=',';
    text[89]=' ';
    text[90]=e5[0];
    text[91]=e5[1];
    text[92]=e5[2];
    text[93]=',';

    for(i=0;i<length;i++){

    if(text[i-4]=='1' && text[i-2]=='T' && text[i-1]=='L'){
        text[i] = '\n';
    }
    if(text[i-5]=='.' && text[i-4]=='5' && text[i-2]=='T' && text[i-1]=='L'){
        text[i] = '\n';
    }
     if(text[i-6]=='.' && text[i-5]=='7' && text[i-4]=='5' && text[i-2]=='T' && text[i-1]=='L'){
        text[i] = '\n';
    }

}

    for(i=0;i<99;i++){
      Serial.print(text[i]);
    }
}

void isle(){
    Serial.println();
    Serial.print("-----Güncel Stok Durumu------"); Serial.println();
    Serial.print("1 TL Sayısı : "); Serial.print(moneycounts[2]); Serial.println();
    Serial.print("50 KRS Sayısı : "); Serial.print(moneycounts[1]); Serial.println();
    Serial.print("25 KRS Sayısı : "); Serial.print(moneycounts[0]); Serial.println();
    Serial.print("Su Sayısı : "); Serial.print(itemc[0][2]); Serial.println();
    Serial.print("Çay Sayısı : "); Serial.print(itemc[1][2]); Serial.println();
    Serial.print("Kahve Sayısı : "); Serial.print(itemc[2][2]); Serial.println();
    Serial.print("Çikolota Sayısı : "); Serial.print(itemc[3][2]); Serial.println();
    Serial.print("Bisküvi Sayısı : "); Serial.print(itemc[4][2]); Serial.println();
    Serial.print("------------------"); Serial.println();
}

void reset(){



   bakiye = 0;
   harcananpara = 0;

   proc1 = 0 ,   proc2 = 0;      proc3 = 0;      proc4 = 0;      proc5 = 0;

   moneycounts[0] = moneycounts[0] - money11;
   moneycounts[1] = moneycounts[1] - money22;
   moneycounts[2] = moneycounts[2] - money33;

   money11 = 0; money22 = 0; money33 = 0;
   control = 0;
   isle();

}

void paraUstu(){

   paraustu = bakiye - harcananpara;

   kasatop = moneycounts[0]*0.25 + moneycounts[1]*0.5 + moneycounts[2];

   if(kasatop < paraustu){

        lcd.clear();
        lcd.print("Kasada yeterli");
        lcd.setCursor(0,1);
        lcd.print("para yok !");
        lcd.setCursor(1,0);

   }

   if(paraustu == 0){

      lcd.clear();
      lcd.print("Paraustu ");
      lcd.setCursor(0,1); lcd.print("verilmeyecektir."); lcd.setCursor(1,0);


   }
   if(bakiye < harcananpara){

      lcd.clear();
      lcd.print("Yetersiz bakiye!");
      bakiye = 0;
      harcananpara = 0;
      if(money11 != 0){

        moneycounts[0] = moneycounts[0] - money11;
      }
      if(money22 != 0){

        moneycounts[1] = moneycounts[1] - money22;
      }
      if(money33 != 0){

        moneycounts[2] = moneycounts[2] - money33;
      }

   }

   if(bakiye > harcananpara){

       for(i = 2 ; i >= 0 ; i--){

           if(moneycounts[i]>0 && para[i]<= paraustu){

                adets = paraustu/para[i];

           if(i==2 && adets>moneycounts[2]){

                adets = moneycounts[2];

            }
           if(i==1 && adets>moneycounts[1]){

                adets=moneycounts[1];

            }
           if(i==0 && adets>moneycounts[0]){

                adets=moneycounts[0];
          }

          if(i==2){

          paraustu = paraustu-(1*adets);
          kasatop = kasatop-adets;

          }

          if(i==1){

          paraustu=paraustu-(0.5*adets);
          kasatop=kasatop-(0.5*adets);

       }

          if(i==0){

           paraustu=paraustu-(0.25*adets);
           kasatop=kasatop-(0.25*adets);

       }


          if(i==2){

           lcd.clear();
           lcd.print(adets); lcd.print("adet 1TL");

          }

          if(i==1){

           lcd.setCursor(0,1);
           lcd.print(adets); lcd.print("x 50kr");

          }

          if(i==0){


           lcd.print(" "); lcd.print(adets); lcd.print("x 25kr");

          }
           moneycounts[i] = moneycounts[i]-adets;
   }
}
   }
   money11 = 0; money22 = 0; money33 = 0;
   }

void setup()
{

  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(BUTON1,INPUT_PULLUP);
  pinMode(BUTON2,INPUT_PULLUP);
  pinMode(BUTON3,INPUT_PULLUP);
  pinMode(BUTON4,INPUT_PULLUP);
  pinMode(BUTON5,INPUT_PULLUP);
  pinMode(RESET,INPUT_PULLUP);
  pinMode(BITIS, INPUT_PULLUP);
  pinMode(LEDY,OUTPUT);
  pinMode(LEDK,OUTPUT);
  digitalWrite(LEDY,HIGH);
  digitalWrite(LEDK,HIGH);


    length=strlen(text);
    moneycount[0]=strtok(text,",");
    moneycount[1]=strtok(NULL,",");
    moneycount[2]=strtok(NULL,"\n");
    for(i=0;i<3;i++){
      moneycounts[i] = atof(moneycount[i]);
    }

        item[0][0]=strtok(NULL,",");
        item[0][1]=strtok(NULL,",");
        item[0][2]=strtok(NULL,",");
        itemc[0][2]=atoi(item[0][2]);
        item[0][3]=strtok(NULL,"\n");

        item[1][0]=strtok(NULL,",");
        item[1][1]=strtok(NULL,",");
        item[1][2]=strtok(NULL,",");
        itemc[1][2]=atoi(item[1][2]);
        item[1][3]=strtok(NULL,"\n");

        item[2][0]=strtok(NULL,",");
        item[2][1]=strtok(NULL,",");
        item[2][2]=strtok(NULL,",");
        itemc[2][2]=atoi(item[2][2]);
        item[2][3]=strtok(NULL,"\n");

        item[3][0]=strtok(NULL,",");
        item[3][1]=strtok(NULL,",");
        item[3][2]=strtok(NULL,",");
        itemc[3][2]=atoi(item[3][2]);
        item[3][3]=strtok(NULL,"\n");

        item[4][0]=strtok(NULL,",");
        item[4][1]=strtok(NULL,",");
        item[4][2]=strtok(NULL,",");
        itemc[4][2]=atoi(item[4][2]);
        item[4][3]=strtok(NULL,"\n");

    for(i=0;i<5;i++){
        for(int j=0;j<4;j++){
            items[i][j]=atof(item[i][j]);
                if(i==0 && j==3){
                 items[i][j]=0.5;
        }

    }   } }

void loop()
{

  if((digitalRead(BUTON1)==0))
  {
    if(control%2 == 0){
        money1 = money1 + 1;
        bakiye = bakiye + 0.25;
        lcd.clear(); lcd.print(bakiye); lcd.print(" TL atildi");
    }

    if(control%2 == 1){

       lcd.clear();
       lcd.print(proc1+1); lcd.print(" adet Su alindi.");
       delay(200);
       proc1 = proc1 + 1;

    }
     while(digitalRead(BUTON1==0))
     {

     }
   delay(200);

  }

  if((digitalRead(BUTON2)==0))
  {
     if(control%2 == 0)
{
        money2 = money2 + 1;
        bakiye = bakiye + 0.5;
        lcd.clear(); lcd.print(bakiye); lcd.print(" TL atildi");

 }
    if(control%2 == 1){

       lcd.clear();
       lcd.print(proc2+1); lcd.print(" adet"); lcd.setCursor(0,1); lcd.print("Cay alindi."); lcd.setCursor(1,0);
       delay(200);
       proc2 = proc2 + 1;

    }

     while(digitalRead(BUTON2==0))
    {

     }

   delay(200);
  }

  if((digitalRead(BUTON3)==0))
  {

    if(control%2 == 0){

        money3 = money3 + 1;
        bakiye = bakiye + 1;
        lcd.clear(); lcd.print(bakiye); lcd.print(" TL atildi");

    }

    if(control%2 == 1){

       lcd.clear();
       lcd.print(proc3+1); lcd.print(" adet"); lcd.setCursor(0,1); lcd.print("Kahve alindi."); lcd.setCursor(1,0);
       delay(200);
       proc3 = proc3 + 1;

    }

     while(digitalRead(BUTON3==0))
    {

     }

   delay(200);
  }

  if(digitalRead(BUTON4) == 0){


    if(control%2 == 1){

       lcd.clear();
       lcd.print(proc4+1); lcd.print(" adet"); lcd.setCursor(0,1); lcd.print("Cikolata alindi."); lcd.setCursor(1,0);
       delay(200);
       proc4 = proc4 + 1;

    }

    while(digitalRead(BUTON4==0)){

    }
    delay(200);
  }


  if(digitalRead(BUTON5) == 0){

    if(control%2 == 1){

       lcd.clear();
       lcd.print(proc5+1); lcd.print(" adet"); lcd.setCursor(0,1); lcd.print("Biskuvi alindi."); lcd.setCursor(1,0);
       delay(200);
       proc5 = proc5 + 1;

    }

    while(digitalRead(BUTON5==0)){

    }
    delay(200);
  }

   if(digitalRead(RESET) == 0){
   RESET:

        reset();

        lcd.clear();
        lcd.print("RESETLENDI");
        delay(1000);
        lcd.clear();

    while(digitalRead(RESET==0)){

    }
    delay(200);
  }



  if((digitalRead(BITIS)==0))
  {
     ending = 1+rand()%4;
     lcd.clear();

    if(ending == 2 && control%2 == 1 ){

      digitalWrite(LEDK,LOW);
      delay(300);
      digitalWrite(LEDK,HIGH);

      lcd.clear();
      lcd.print("Para sikisti");

      proc1 = 0 ,   proc2 = 0;      proc3 = 0;      proc4 = 0;      proc5 = 0;

      control=0;
      goto RESET;
    }
    if(control%2 == 0){

      digitalWrite(LEDY,LOW);
      delay(300);
      digitalWrite(LEDY,HIGH);

    bakiye = 0;
    bakiye = bakiye + money1*1/4 + money2*1/2 + money3;

    moneycounts[0] = moneycounts[0] + money1;
    moneycounts[1] = moneycounts[1] + money2;
    moneycounts[2] = moneycounts[2] + money3;

    display = money1*1/4 + money2*1/2 + money3*1;
    lcd.clear();
    lcd.print(display); lcd.print(" TL yuklendi.");

    money11 = money1 , money22 = money2 , money33 = money3;
    money1 = 0; money2 = 0; money3 = 0;
    }
    if(control%2 == 1){

      digitalWrite(LEDY,LOW);
      delay(300);
      digitalWrite(LEDY,HIGH);

      itemc[0][2] = itemc[0][2] - proc1;
      itemc[1][2] = itemc[1][2] - proc2;
      itemc[2][2] = itemc[2][2] - proc3;
      itemc[3][2] = itemc[3][2] - proc4;
      itemc[4][2] = itemc[4][2] - proc5;

      harcananpara = harcananpara + proc1*items[0][3] + proc2*items[1][3] + proc3*items[2][3] + proc4*items[3][3] + proc5*items[4][3];

      proc11 = proc1 , proc22 = proc2 , proc33 = proc3 , proc44 = proc4 , proc55 = proc5;
      proc1 = 0 ,   proc2 = 0;      proc3 = 0;      proc4 = 0;      proc5 = 0;

      paraUstu();
      bakiye = 0;
      isle();
      textIsle();
    }

     while(digitalRead(BITIS==0))
    {

     }
   control++;

   delay(200);
  }



}
