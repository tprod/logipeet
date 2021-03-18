-- MySQL Script generated by MySQL Workbench
-- Thu Mar 18 22:06:22 2021
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Login`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Login` (
  `idLogin` INT NOT NULL,
  `date_hour_in` DATETIME NULL,
  `date_hour_out` DATETIME NULL,
  PRIMARY KEY (`idLogin`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Events`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Events` (
  `idEvents` INT NOT NULL,
  `event_init` DATETIME NULL,
  `event_fin` DATETIME NULL,
  `event_type` INT NULL,
  `event_name` VARCHAR(45) NULL,
  PRIMARY KEY (`idEvents`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Animals`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Animals` (
  `idAnimals` INT NOT NULL AUTO_INCREMENT,
  `name_animal` VARCHAR(45) NULL,
  `history_animal` VARCHAR(45) NULL,
  `photo_animal` VARCHAR(45) NULL,
  `race_animal` VARCHAR(45) NULL,
  PRIMARY KEY (`idAnimals`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Status_sen`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Status_sen` (
  `idStatus_sen` INT NOT NULL AUTO_INCREMENT,
  `status_sen` VARCHAR(45) NULL,
  `log_sens` VARCHAR(45) NULL,
  PRIMARY KEY (`idStatus_sen`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Sensors`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Sensors` (
  `idSensors` INT NOT NULL AUTO_INCREMENT,
  `type_sensor` VARCHAR(45) NULL,
  `Status_sen_idStatus_sen` INT NOT NULL,
  PRIMARY KEY (`idSensors`, `Status_sen_idStatus_sen`),
  INDEX `fk_Sensors_Status_sen1_idx` (`Status_sen_idStatus_sen` ASC) VISIBLE,
  CONSTRAINT `fk_Sensors_Status_sen1`
    FOREIGN KEY (`Status_sen_idStatus_sen`)
    REFERENCES `mydb`.`Status_sen` (`idStatus_sen`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`In_Out_Can`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`In_Out_Can` (
  `id_inout_c` INT NOT NULL AUTO_INCREMENT,
  `time_in_c` DATETIME NULL,
  `time_out_c` DATETIME NULL,
  PRIMARY KEY (`id_inout_c`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Cannil`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Cannil` (
  `idCannil` INT NOT NULL AUTO_INCREMENT,
  `name_cannil` VARCHAR(45) NULL,
  `adress_cannil` VARCHAR(45) NULL,
  `coordinates_cannil` VARCHAR(45) NULL,
  `Animals_idAnimals` INT NOT NULL,
  `Sensors_idSensors` INT NOT NULL,
  `In_Out_Can_id_inout_c` INT NOT NULL,
  PRIMARY KEY (`idCannil`, `Animals_idAnimals`, `Sensors_idSensors`, `In_Out_Can_id_inout_c`),
  INDEX `fk_Cannil_Annimals1_idx` (`Animals_idAnimals` ASC) VISIBLE,
  INDEX `fk_Cannil_Sensors1_idx` (`Sensors_idSensors` ASC) VISIBLE,
  INDEX `fk_Cannil_In_Out_Can1_idx` (`In_Out_Can_id_inout_c` ASC) VISIBLE,
  CONSTRAINT `fk_Cannil_Annimals1`
    FOREIGN KEY (`Animals_idAnimals`)
    REFERENCES `mydb`.`Animals` (`idAnimals`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Cannil_Sensors1`
    FOREIGN KEY (`Sensors_idSensors`)
    REFERENCES `mydb`.`Sensors` (`idSensors`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Cannil_In_Out_Can1`
    FOREIGN KEY (`In_Out_Can_id_inout_c`)
    REFERENCES `mydb`.`In_Out_Can` (`id_inout_c`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`In_Out_Stor`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`In_Out_Stor` (
  `idIn_Out_Stor` INT NOT NULL,
  `time_in_s` DATETIME NULL,
  `time_out_s` DATETIME NULL,
  PRIMARY KEY (`idIn_Out_Stor`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`User`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`User` (
  `idUser` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  `email` VARCHAR(45) NULL,
  `password` VARCHAR(45) NULL,
  `age` INT NULL,
  `sex` INT NULL,
  `address` VARCHAR(45) NULL,
  `phone` VARCHAR(45) NULL,
  `type_user` INT NULL,
  `Login_idLogin` INT NOT NULL,
  `Events_idEvents` INT NOT NULL,
  `Cannil_idCannil` INT NOT NULL,
  `In_Out_Can_id_inout_c` INT NOT NULL,
  `In_Out_Stor_idIn_Out_Stor` INT NOT NULL,
  `In_Out_Can_id_inout_c1` INT NOT NULL,
  PRIMARY KEY (`idUser`, `Login_idLogin`, `Events_idEvents`, `Cannil_idCannil`, `In_Out_Can_id_inout_c`, `In_Out_Stor_idIn_Out_Stor`, `In_Out_Can_id_inout_c1`),
  INDEX `fk_User_Login_idx` (`Login_idLogin` ASC) VISIBLE,
  INDEX `fk_User_Events1_idx` (`Events_idEvents` ASC) VISIBLE,
  INDEX `fk_User_Cannil1_idx` (`Cannil_idCannil` ASC) VISIBLE,
  INDEX `fk_User_In_Out_Stor1_idx` (`In_Out_Stor_idIn_Out_Stor` ASC) VISIBLE,
  INDEX `fk_User_In_Out_Can1_idx` (`In_Out_Can_id_inout_c1` ASC) VISIBLE,
  CONSTRAINT `fk_User_Login`
    FOREIGN KEY (`Login_idLogin`)
    REFERENCES `mydb`.`Login` (`idLogin`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_User_Events1`
    FOREIGN KEY (`Events_idEvents`)
    REFERENCES `mydb`.`Events` (`idEvents`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_User_Cannil1`
    FOREIGN KEY (`Cannil_idCannil`)
    REFERENCES `mydb`.`Cannil` (`idCannil`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_User_In_Out_Stor1`
    FOREIGN KEY (`In_Out_Stor_idIn_Out_Stor`)
    REFERENCES `mydb`.`In_Out_Stor` (`idIn_Out_Stor`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_User_In_Out_Can1`
    FOREIGN KEY (`In_Out_Can_id_inout_c1`)
    REFERENCES `mydb`.`In_Out_Can` (`id_inout_c`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Storage`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Storage` (
  `idStorage` INT NOT NULL AUTO_INCREMENT,
  `name_product` VARCHAR(45) NULL,
  `code_product` VARCHAR(45) NULL,
  `weight` VARCHAR(45) NULL,
  `User_idUser` INT NOT NULL,
  `User_Login_idLogin` INT NOT NULL,
  `User_Events_idEvents` INT NOT NULL,
  `User_Cannil_idCannil` INT NOT NULL,
  `User_In_Out_Can_id_inout_c` INT NOT NULL,
  `In_Out_Stor_idIn_Out_Stor` INT NOT NULL,
  PRIMARY KEY (`idStorage`, `User_idUser`, `User_Login_idLogin`, `User_Events_idEvents`, `User_Cannil_idCannil`, `User_In_Out_Can_id_inout_c`, `In_Out_Stor_idIn_Out_Stor`),
  INDEX `fk_Storage_User1_idx` (`User_idUser` ASC, `User_Login_idLogin` ASC, `User_Events_idEvents` ASC, `User_Cannil_idCannil` ASC, `User_In_Out_Can_id_inout_c` ASC) VISIBLE,
  INDEX `fk_Storage_In_Out_Stor1_idx` (`In_Out_Stor_idIn_Out_Stor` ASC) VISIBLE,
  CONSTRAINT `fk_Storage_User1`
    FOREIGN KEY (`User_idUser` , `User_Login_idLogin` , `User_Events_idEvents` , `User_Cannil_idCannil` , `User_In_Out_Can_id_inout_c`)
    REFERENCES `mydb`.`User` (`idUser` , `Login_idLogin` , `Events_idEvents` , `Cannil_idCannil` , `In_Out_Can_id_inout_c`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Storage_In_Out_Stor1`
    FOREIGN KEY (`In_Out_Stor_idIn_Out_Stor`)
    REFERENCES `mydb`.`In_Out_Stor` (`idIn_Out_Stor`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
