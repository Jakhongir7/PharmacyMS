
insert into authorization values ('1000', '1000', 0);
insert into authorization values ('1121', '12345', 1);
insert into authorization values ('1122', '12345', 1);
insert into authorization values ('1123', '12345', 1);
insert into authorization values ('1124', '12345', 1);
insert into authorization values ('1125', '54321', 2);
insert into authorization values ('1126', '54321', 2);
insert into authorization values ('1127', '54321', 2);
insert into authorization values ('1128', '54321', 2);
insert into company values ('1122', 'Palfo', 'Tashkent', '+998901234567');
insert into company values ('1123', 'BioPharma', 'Andijan', '+998901234566');
insert into company values ('1124', 'Avantika', 'Bukhara', '+998901234568');
insert into company values ('1121', 'Uzkimyofarm', 'Samarkand', '+998901234587');
insert into drugstore values ('1125', '777', 'Tashkent','+998996546756');
insert into drugstore values ('1126', '999', 'Chilonzor', '+998907546788');
insert into drugstore values ('1127', 'Apteka', 'Bozbazar', '+79098898');
insert into drugstore values ('1128', 'dorixona', 'Karasu', '+998945678765');
insert into medicine values ('m001', 'Trimol', 'For headache', 5000, '1123');
insert into medicine values ('m002', 'Sinepar', 'For ache.', 4000, '1122');
insert into medicine values ('m003', 'Parasetamol', 'Temperature', 1000, '1123');
insert into medicine values ('m004', 'Teraflu', 'Flu', 7000, '1124');
insert into medicine values ('m005', 'Sefazalin', 'For Immunes', 3000, '1121');
insert into medicine values ('m006', 'DoctorMoM', 'For throat', 2000, '1123');
insert into medicine values ('m007', 'Vazelin', 'For ache', 2500,'1123');
insert into medicine values ('m008', 'Streptotsit', 'For Throat', 4500, '1124');
insert into journal(comp_id, store_id, med_id, quantity, status) values ('1124', '1125', 'm004', 100, 0);
insert into journal(comp_id, store_id, med_id, quantity, status) values ('1121', '1125', 'm005', 200, 0);
insert into journal(comp_id, store_id, med_id, quantity, status) values ('1124', '1126', 'm004', 100, 0);
insert into journal(comp_id, store_id, med_id, quantity, status) values ('1123', '1125', 'm003', 100, 0);
INSERT INTO inventory VALUES ('1125', 'm005', 'Sefazalin', 10)
INSERT INTO inventory VALUES ('1125', 'm008', 'Streptotsit', 3)
INSERT INTO inventory VALUES ('1125', 'm002', 'Sinepar', 50)
INSERT INTO inventory VALUES ('1125', 'm003', 'Parasetamol', 9)

