#!/usr/bin/env bash


#git pull origin dev
mkdir -p ../../../../../db_backup
drush sql-dump > ../../../../../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)
#drush sql-dump > ../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)

cp -avr patches/files/jquery.imagesloaded ../../libraries
cp -avr patches/files/jquery.imgareaselect ../../libraries
cp -avr patches/files/manualcrop ../
drush cc all
drush en -y manualcrop
drush fr -y fu_ansicht

drush cc all