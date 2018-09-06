#!/bin/bash

curHour=$(date "+%H")

if [ ${curHour} > 18 ]
then
	echo "${curHour}"
fi

