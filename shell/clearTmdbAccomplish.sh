#!/bin/bash
HOSTNAME="192.168.19.192"
PORT="3306"
USERNAME="tradepro"
PASSWORD="trading"

DBNAME="cpp_quantdo_hxw"
TABLENAME="to_tmdbaccomplish"

insert_sql="insert into ${TABLENAME} values(1,1)"

mysql -h${HOSTNAME} -p${PORT} -u${USERNAME} -p${PASSWORD} ${DBNAME} -e "${insert_sql}"



