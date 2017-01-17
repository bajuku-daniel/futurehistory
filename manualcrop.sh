#!/usr/bin/env bash


#git pull origin dev
mkdir -p ../../../../../db_backup
drush sql-dump > ../../../../../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)

cp -avr patches/files/jquery.imagesloaded ../../libraries
cp -avr patches/files/jquery.imgareaselect ../../libraries

drush cc all
drush dl -y manualcrop
drush en -y manualcrop



cp patches/manualcrop_modify.patch ../manualcrop/manualcrop_modify.patch
cd .. && cd manualcrop && patch < manualcrop_modify.patch
echo "##################  PATCH"

#drush fr -y fu_ansicht

drush cc all