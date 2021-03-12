CREATE TABLE `Animals`
(
 `id_animal`      int NOT NULL AUTO_INCREMENT ,
 `id_cannil`      int NOT NULL ,
 `name_animal`    varchar(45) NOT NULL ,
 `history_animal` varchar(45) NOT NULL ,
 `photo_animal`   varchar(45) NOT NULL ,
 `race_animal`    varchar(45) NOT NULL ,

PRIMARY KEY (`id_animal`),
KEY `fkIdx_211` (`id_cannil`),
CONSTRAINT `FK_210` FOREIGN KEY `fkIdx_211` (`id_cannil`) REFERENCES `Cannil` (`id_cannil`)
);

CREATE TABLE `Cannil`
(
 `id_cannil`          int NOT NULL AUTO_INCREMENT ,
 `id_user`            int NOT NULL ,
 `name_cannil`        varchar(45) NOT NULL ,
 `adress_cannil`      varchar(45) NOT NULL ,
 `coordinates_cannil` varchar(45) NOT NULL ,

PRIMARY KEY (`id_cannil`),
KEY `fkIdx_173` (`id_user`),
CONSTRAINT `FK_172` FOREIGN KEY `fkIdx_173` (`id_user`) REFERENCES `User` (`id_user`)
);

CREATE TABLE `Events`
(
 `id_events`  int NOT NULL AUTO_INCREMENT ,
 `id_user`    int NOT NULL ,
 `event_init` datetime NOT NULL ,
 `event_fin`  datetime NOT NULL ,
 `event_type` tinyint NOT NULL ,
 `event_name` varchar(45) NOT NULL ,

PRIMARY KEY (`id_events`),
KEY `fkIdx_186` (`id_user`),
CONSTRAINT `FK_185` FOREIGN KEY `fkIdx_186` (`id_user`) REFERENCES `User` (`id_user`)
);

CREATE TABLE `In_Out_Can`
(
 `id_inout_c` int NOT NULL AUTO_INCREMENT ,
 `id_user`    int NOT NULL ,
 `id_cannil`  int NOT NULL ,
 `time_in_c`  datetime NOT NULL ,
 `time_out_c` datetime NOT NULL ,

PRIMARY KEY (`id_inout_c`),
KEY `fkIdx_192` (`id_cannil`),
CONSTRAINT `FK_191` FOREIGN KEY `fkIdx_192` (`id_cannil`) REFERENCES `Cannil` (`id_cannil`),
KEY `fkIdx_195` (`id_user`),
CONSTRAINT `FK_194` FOREIGN KEY `fkIdx_195` (`id_user`) REFERENCES `User` (`id_user`)
);



CREATE TABLE `Login`
(
 `id_login`      int NOT NULL AUTO_INCREMENT ,
 `id_user`       int NOT NULL ,
 `date_hour_in`  datetime NOT NULL ,
 `date_hour_out` datetime NOT NULL ,

PRIMARY KEY (`id_login`),
KEY `fkIdx_167` (`id_user`),
CONSTRAINT `FK_166` FOREIGN KEY `fkIdx_167` (`id_user`) REFERENCES `User` (`id_user`)
);

CREATE TABLE `Sensors`
(
 `id_sensor`   int NOT NULL ,
 `id_cannil`   int NOT NULL ,
 `type_sensor` varchar(45) NOT NULL ,

PRIMARY KEY (`id_sensor`),
KEY `fkIdx_217` (`id_cannil`),
CONSTRAINT `FK_216` FOREIGN KEY `fkIdx_217` (`id_cannil`) REFERENCES `Cannil` (`id_cannil`)
);

CREATE TABLE `Status_Sen`
(
 `id_status`   int NOT NULL AUTO_INCREMENT ,
 `id_sensor`   int NOT NULL ,
 `status_sens` bit NOT NULL ,
 `log_sens`    varchar(45) NOT NULL ,

PRIMARY KEY (`id_status`),
KEY `fkIdx_220` (`id_sensor`),
CONSTRAINT `FK_219` FOREIGN KEY `fkIdx_220` (`id_sensor`) REFERENCES `Sensors` (`id_sensor`)
);

CREATE TABLE `Storage`
(
 `id_product`   int NOT NULL AUTO_INCREMENT ,
 `id_user`      int NOT NULL ,
 `id_inout`     int NOT NULL ,
 `name_product` varchar(45) NOT NULL ,
 `code_product` varbinary(45) NOT NULL ,
 `weight`       int NOT NULL ,

PRIMARY KEY (`id_product`),
KEY `fkIdx_179` (`id_user`),
CONSTRAINT `FK_178` FOREIGN KEY `fkIdx_179` (`id_user`) REFERENCES `User` (`id_user`),
KEY `fkIdx_204` (`id_inout`),
CONSTRAINT `FK_203` FOREIGN KEY `fkIdx_204` (`id_inout`) REFERENCES `In_Out_Stor` (`id_inout`)
);

CREATE TABLE `User`
(
 `id_user`    int NOT NULL AUTO_INCREMENT ,
 `name`       varchar(45) NOT NULL ,
 `email`      varchar(45) NOT NULL ,
 `password`   varchar(45) NOT NULL ,
 `age`        int NOT NULL ,
 `sex`        tinyint NOT NULL ,
 `address`    varchar(45) NOT NULL ,
 `phone`      varchar(9) NOT NULL ,
 `type_user`  decimal NOT NULL ,
 `permission` bit NOT NULL ,

PRIMARY KEY (`id_user`)
);











