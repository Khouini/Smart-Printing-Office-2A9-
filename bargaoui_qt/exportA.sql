--------------------------------------------------------
--  File created - Thursday-April-21-2022   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table EMPLOYE
--------------------------------------------------------

  CREATE TABLE "WAHCHI"."EMPLOYE" 
   (	"ID_E" VARCHAR2(20 BYTE), 
	"NOM" VARCHAR2(20 BYTE)
   ) SEGMENT CREATION IMMEDIATE 
  PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into WAHCHI.EMPLOYE
SET DEFINE OFF;
Insert into WAHCHI.EMPLOYE (ID_E,NOM) values ('60 98 DE 2C','ahmed');
Insert into WAHCHI.EMPLOYE (ID_E,NOM) values ('86 ED 2A 21','mohamed');
Insert into WAHCHI.EMPLOYE (ID_E,NOM) values ('4695489','yacine');
Insert into WAHCHI.EMPLOYE (ID_E,NOM) values (null,null);
