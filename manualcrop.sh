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
drush vset fu_manualcrop_enabled true
drush cc all

## TODOS
# checkout html
# checkoout entdecken ..
# cp /futurehistory_entdecken/futurehistory_entdecken_poi_bbox.inc