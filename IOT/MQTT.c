mosquitto_sub -t cdac/acts/desd -h localhost -p 1883 
 1664  mosquitto_sub -t cdac/acts/desd -h 192.168.76.240 -p 1883 
 1665  mosquitto_sub -t cdac/acts/desd -h localhost  -p 1883 
 1666  mosquitto_sub -t cdac/acts/desd -h localhost -p 1883 
 1667  mosquitto_sub -t +/+/+ -h localhost -p 1883 
 1668  mosquitto_sub -t # -h localhost -p 1883 
 1669  mosquitto_sub -t /# -h localhost -p 1883 
 1670  mosquitto_sub -t /\# -h localhost -p 1883 
 1671  mosquitto_sub -t +/# -h localhost -p 1883 
 1672  mosquitto_sub -t \# -h localhost -p 1883 
 1673  mosquitto_sub -t +\# -h localhost -p 1883 
 1674  mosquitto_sub -t +/# -h localhost -p 1883 
 1675  mosquitto_sub -t \# -h localhost -p 1883 
 1676  sudo install mosquitto
 1677  sudo apt install mosquitto
 1678  sudo apt install mosquitto-clients
 1679  mosquitto --v
 1680  sudo service mosquitto status
 1681  sudo netstat -naltp | grep mosquitto
 1682  lsp release
 1683  uname -a
 1684  cd /etc/mosquitto
 1685  ls
 1686  cat mosquitto.conf 
 1687  cat mosquitto.log
 1688  sudo cat mosquitto.log
 1689  ls
 1690  cd ..
 1691  ls
 1692  sudo cat mosquitto.log
 1693  cd
 1694  sudo cat mosquitto.log
 1695  cs /var/lib/mosquito/
 1696  cd /var/lib/mosquito/
 1697  cd /var/lib/mosquitto/
 1698  ls
 1699  sudo cat mosquitto.log
 1700  cd ..
 1701  var log
 1702  cd log
 1703  cd mosquitto/
 1704  ls
 1705  cat mosquitto.log 
 1706  sudo cat mosquitto.log 
 1707  cd ..
 1708  cd
 1709  cd home
 sudo nano allowall.conf
 1723  vi allowall.conf
 1724  sudo netstat -naltp | grep 1883
 1725  vi allowall.conf
 1726  sudo service mosquitto restart
 1727  sudo service mosquitto status
 1728  sudo netstat -naltp | grep 1883
 1729  cd
  mosquitto_pub -t cdac/acts/desd -h localhost -p 1883 -m "hello,DESD!"
 1744  mosquitto_pub -t cdac/acts/desd -h localhost -p 1883 -l
 1745  mosquitto_pub -t cdac/acts/desd -h 192.168.76.240 -p 1883 -m "gautum" -l
 1746  mosquitto_pub -t cdac/acts/desd -h 192.168.76.240 -p 1883 -l "gautum" 
 1747  mosquitto_pub -t cdac/acts/desd -h 192.168.76.240 -p 1883 -l 
 1748  mosquitto_pub -t cdac/acts/desd -h localhost -p 1883 -l 
 1749  mosquitto_pub -t cdac/acts/desd -h 192.168.76.236 -p 1883 -l 
 1750  mosquitto_pub -t cdac/acts/desd -h 192.168.76.240 -p 1883 -l 
 1751  mosquitto_pub -t -p  cdac/acts/desd -h 192.168.76.240 -p 1883 -l 
 1752  mosquitto_pub -t -dcdac/acts/desd -h 192.168.76.240 -p 1883 -l 
 1753  mosquitto_pub -t cdac/acts/desd -h 192.168.76.236 -p 1883 -l 
 1754  mosquitto_pub -t cdac/acts/desd -h 192.168.76.236 -p 1883 -l -d
 1755  mosquitto_pub -t cdac/acts/desd -h 192.168.40.225 -p 1883 -l -d
 1756  mosquitto_pub -t cdac/acts/desd -h 192.168.76.236 -p 1883 -l -d
 1757  mosquitto_pub -t cdac/acts/desd -h localhost -p 1883 -l -d
 1758  mosquitto_pub -t +/+/+ -h localhost -p 1883 -l -d
 1759  mosquitto_pub -t cdac/acts/desd -h localhost -p 1883 -l -d




2  scp -r *.*  debian@192.168.76.236:~/./harshitedd
 1863  scp -r *.*  desd@192.168.76.236:~/./harshitedd
 1864  scp -r Q2  desd@192.168.76.236:~/./harshitedd
 1865  scp -r Q2  desd@192.168.76.236:~/./
 1866  scp -r Q2  desd@192.168.76.236:~/./Desktop/harshit
 1867  scp -r mod33.ko debian@192.168.7.2:~/.
 1868  scp -r mod34.ko debian@192.168.7.2:~/.
 1869  ssh debian@192.168.7.2
 1870  udo su
 1871  sudo su
 1872  ssh debian@192.168.7.2
 1873  ssh debian@192.168.7.2
 1874  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1875  scp -r q3.ko  debian@192.168.7.2:~/.
 1876  make clean
 1877  xlear
 1878  clear
 1879  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1880  scp -r q2.ko  debian@192.168.7.2:~/.
 1881  ssh desd@192.168.76.236
 1882  ssh desd@192.168.40.236
 1883  ssh desd@192.168.76.236
 1884  ifconfig
 1885  vi q1.c
 1886  vi que1.c
 1887  vim q2.c
 1888  make clean
 1889  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1890  ssh debian@192.168.7.2
 1891  clear
 1892  ssh debian@192.168.7.2
 1893  clear
 1894  ssh debian@192.168.7.2
 1895  make clean
 1896  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1897  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1898  scp -r que.ko  debian@192.168.7.2:~/.
 1899  scp -r que1.ko  debian@192.168.7.2:~/.
 1900  make clean
 1901  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1902  scp -r que1.ko  debian@192.168.7.2:~/.
 1903  make clean
 1904  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1905  scp -r q1.ko  debian@192.168.7.2:~/.
 1906  ssh desd@192.168.76.190
 1907  make clean
 1908  ssh debian@192.168.7.2
 1909  make clean
 1910  ssh debian@192.168.7.2
 1911  make clean
 1912  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1913  make clean
 1914  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1915  vi q2_user.c
 1916  make clean
 1917  make clean
 1918  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1919  scp -r q1.ko  debian@192.168.7.2:~/.
 1920  scp -r que.ko  debian@192.168.7.2:~/.
 1921  scp -r que1.ko  debian@192.168.7.2:~/.
 1922  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1923  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1924  make clean
 1925  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1926  gcc q2_user.c
 1927  scp -r q2.ko q2_user.c  debian@192.168.7.2:~/.
 1928  make clean
 1929  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1930  ssh debian@192.168.7.2
 1931  make clean
 1932  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1933  scp -r que2_kernel.ko que2.c  debian@192.168.7.2:~/.
 1934  scp -r q2_kernel.ko que2.c  debian@192.168.7.2:~/.
 1935  make clean
 1936  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1937  make clean
 1938  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1939  vi que2.c
 1940  make clean
 1941  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1942  scp -r q2.ko q2_user.c  debian@192.168.7.2:~/.
 1943  make clean
 1944  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 1945  vi q2_kernel.c
 1946  ssh debian@192.168.7.2
 1947  mosquitto_pub -t cdac/acts/desd -h localhost -p 1883 -m
 1948  mosquitto_pub -t cdac/acts/desd -h localhost -p 1883 -l
 1949  mosquitto_pub -t cdac/acts/desd -h localhost -p 1883 -l -d
 1950  mosquitto_pub -t cdac/acts/desd -q 2 -h localhost -p 1883 -l -d
 1951  mosquitto_pub -t cdac/acts/desd -q 1 -h localhost -p 1883 -l -d
 1952  mosquitto_pub -t cdac/acts/desd -q 0 -h localhost -p 1883 -l -d
 1953  mosquitto_pub -t cdac/acts/desd -q 2 -h localhost -p 1883 -l -d
 1954  mosquitto_pub -t cdac/acts/desd -q 0 -h localhost -p 1883 -l -d
 1955  mosquitto_pub -t cdac/acts/desd -q 1 -h localhost -p 1883 -l -d
 1956  mosquitto_pub -t cdac/acts/desd -q 1 -h localhost -p 1883 -l -d -r
 1957  mosquitto_pub -t cdac/acts/desd -q 0 -h localhost -p 1883 -l -d -r
 1958  mosquitto_pub -t cdac/acts/desd -q 1 -h localhost -p 1883 -l -d -r
 1959  mosquitto_pub -t cdac/acts/desd -q 2 -h localhost -p 1883 -l -d -r
 1960  mosquitto_pub -t cdac/acts/desd -q 2 -h localhost -p 1883 -l -d -r-n
 1961  mosquitto_pub -t cdac/acts/desd -q 2 -h localhost -p 1883 -l -d -r-m
 1962  mosquitto_pub -t cdac/acts/desd -q 2 -h localhost -p 1883 -l -d -r-m ""
 1963  mosquitto_pub -t cdac/acts/desd -q 2 -h localhost -p -m " " 1883 -l -d -r
 1964  mosquitto_pub -t cdac/acts/desd -q 2 -r  -h localhost -p -m ""
 1965  mosquitto_pub -t cdac/acts/desd -q 0 -r  -h localhost -p -m ""
 1966  mosquitto_pub -t cdac/acts/desd -r  -h localhost -p -m ""
 1967  mosquitto_pub -t cdac/acts/desd -r -h localhost -p -m ""
 1968  mosquitto_pub -t cdac/acts/desd -r -h localhost -p 1883 -m ""
 1969  mosquitto_pub -t cdac/acts/desd -r -h localhost -p -m ""
 1970  mosquitto_pub -t cdac/acts/desd -r -h localhost -p 1883 -m ""
 1971  mosquitto_pub -t cdac/acts/desd -r -h localhost -p 1883 -m "ajay """
 1972  mosquitto_pub -t cdac/acts/desd -r -h localhost -p 1883 -m "ajay"""
 1973  man mosquitto
 1974  mosquitto_pub -t cdac/acts/desd -r -h localhost -p 1883 -m "ajay"""
 1975  mosquitto_pub -t cdac/acts/desd -r -h localhost -p 1883 -m
 1976  mosquitto_pub -t cdac/acts/desd -r -h localhost -p 1883 
 1977  mosquitto_pub -t cdac/acts/desd  -h localhost -p 1883 
 1978  mosquitto_pub -t cdac/acts/desd  -h localhost -p 1883 -l
 1979  mosquitto_pub -t cdac/acts/desd  -h localhost -p 1883 -l -r
 1980  mosquitto_sub -t cdac/acts/desd -h 192.168.76.240 -p 1883 
 1981  mosquitto_sub -t cdac/acts/desd -h localhost -p 1883 
 1982  history
 1983  clear
 1984  ls
 1985  f
 1986  clear
 1987  mosquitto_sub -t cdac/acts/desd -h 192.168.76.240 -p 1883 
 1988  mosquitto_sub -t cdac/acts/desd -h localhost -p 1883 
 1989  mosquitto_sub -t cdac/acts/desd -q 0 -h localhost -p 1883 
 1990  mosquitto_sub -t cdac/acts/desd -q 1 -h localhost -p 1883 
 1991  mosquitto_sub -t cdac/acts/desd -q 2 -h localhost -p 1883 
 1992  mosquitto_sub -t cdac/acts/desd -q 0 -h localhost -p 1883 
 1993  mosquitto_sub -t cdac/acts/desd -q 2 -h localhost -p 1883 
 1994  mosquitto_sub -t cdac/acts/desd  -h localhost -p 1883 
 1995  ajay 
 1996  mosquitto_sub -t cdac/acts/desd  -h localhost -p 1883 
 1997  mosquitto_sub -t cdac/acts/desd  -h localhost -p 1883 -d
 1998  mosquitto_pub -t \# -h test.mosquitto.org -p 1883
 1999  mosquitto_pub -t \+\# -h test.mosquitto.org -p 1883
 2000  mosquitto_pub -t desd/classroom/acts -h test.mosquitto.org -p 1883
 2001  mosquitto_pub -t desd/classroom/acts -h test.mosquitto.org -p 188 -l3
 2002  mosquitto_pub -t desd/classroom/acts -h test.mosquitto.org -p 188 -l
 2003  mosquitto_pub -t desd/classroom/acts -h test.mosquitto.org -p 1883 -l
 2004  mosquitto_pub -t desd/classroom/acts -h -test.mosquitto.org -p 1883 -l
 2005  mosquitto_pub -t desd/classroom/acts -h q1 test.mosquitto.org -p 1883 -l
 2006  mosquitto_pub -t desd/classroom/acts -h q 1 test.mosquitto.org -p 1883 -l
 2007  mosquitto_pub -t desd/classroom/acts -h -q 1 test.mosquitto.org -p 1883 -l
 2008  mosquitto_pub -t desd/classroom/acts -h -q 0 test.mosquitto.org -p 1883 -l
 2009  mosquitto_pub -t desd/classroom/acts -h -q1 test.mosquitto.org -p 1883 -l
 2010  mosquitto_pub -t desd/classroom/acts -h -q0 test.mosquitto.org -p 1883 -l
 2011  mosquitto_pub -t desd/classroom/acts -h -q test.mosquitto.org -p 1883 -l
 2012  mosquitto_pub -t desd/classroom/acts -h  test.mosquitto.org -p 1883 -l
 2013  mosquitto_pub -t desd/classroom/acts1 -h  test.mosquitto.org -p 1883 -l                                                     
 2014  mosquitto_pub -t desd/classroom/acts1 -h  localhost -p 1883 -l                                                     
 2015  mosquitto_pub -t desd/classroom/acts1 -h -q localhost -p 1883 -l                                                     
 2016  mosquitto_pub -t desd/classroom/acts1 -h -q 0 localhost -p 1883 -l                                                     
 2017  mosquitto_pub -t desd/classroom/acts1 -h -q0 localhost -p 1883 -l                                                     
 2018  mosquitto_sub --c
 2019  mosquitto_pub -t desd/classroom/acts1 -h -q localhost -p 1883 -l                                                     
 2020  mosquitto_pub -t desd/classroom/acts1 -h  localhost -p 1883 -l                                                     
 2021  mosquitto_pub -t desd/classroom/acts1 -h -q 1 localhost -p 1883 -l                                                     
 2022  mosquitto_pub -t desd/classroom/acts1 -q 1 -h  localhost -p 1883 -l                                                     
 2023  mosquitto_pub -t desd/classroom/acts1 -q 1 -h  localhost -p 1883 -l -d                                                    
 2024  SYS/broker/clients/connected
 2025  mosquito_sub -t SYS/broker/clients/connected
 2026  mosquito_sub -t \$SYS/broker/clients/connected
 2027  mosquito_sub -t \$SYS/broker/clients/connected -h localhost -p 1883 
 2028  mosquito_sub -t \$SYS/broker/clients/connected -h localhost -p 1883  -l
 2029  mosquitto_sub -t \$SYS/broker/clients/connected -h localhost -p 1883  -l
 2030  mosquitto_sub -t \$SYS/broker/clients/connected -h localhost -p 1883  
 2031  mosquitto_sub -t \$SYS/broker/clients/connected -h
 2032  mosquitto_sub -t \$SYS/broker/clients/connected
 2033  mosquitto_sub -t \$SYS/broker/clients/connected -h test.mosqitto.org 1883
 2034  mosquitto_sub -t \$SYS/broker/clients/connected -h test.mosquitto.org 1883
 2035  mosquitto_sub -t \$SYS/broker/clients/connected -h test.mosquitto.org -p 1883
 2036  mosquitto_pub -t desd/classroom/acts1 -q 1 -h  localhost -p 1883 -l -d -m "ajya"                                                   
 2037  mosquitto_pub -t desd/classroom/acts1 -q 1 -h  localhost -p 1883 -d -m "ajya"                                                   
 2038  mosquitto_pub -t desd/classroom/acts1 -q 1 -r --will-topic desd/classroom/acts1 --will-payload "desd 00" -h   localhost -p 1883 -l                                                     
 2039  mosquitto_pub -t desd/classroom/acts1 -q 1 -r --will-topic desd/classroom/acts1 --will-retain  --will-payload "desd 00" -h   localhost -p 1883 -l                                                     
 2040  histroy
 2041  history
 
 
 
                                       
 1878  mosquitto_pub -t desd/classroom/acts1 -h  localhost -p 1883 -l                                                     
 1879  mosquitto_pub -t desd/classroom/acts1 -h -q 1 localhost -p 1883 -l                                                     
 1880  mosquitto_pub -t desd/classroom/acts1 -q 1 -h  localhost -p 1883 -l                                                     
 1881  mosquitto_pub -t desd/classroom/acts1 -q 1 -h  localhost -p 1883 -l -d                                                    
 1882  SYS/broker/clients/connected
 1883  mosquito_sub -t SYS/broker/clients/connected
 1884  mosquito_sub -t \$SYS/broker/clients/connected
 1885  mosquito_sub -t \$SYS/broker/clients/connected -h localhost -p 1883 
 1886  mosquito_sub -t \$SYS/broker/clients/connected -h localhost -p 1883  -l
 1887  mosquitto_sub -t \$SYS/broker/clients/connected -h localhost -p 1883  -l
 1888  mosquitto_sub -t \$SYS/broker/clients/connected -h localhost -p 1883  
 1889  mosquitto_sub -t \$SYS/broker/clients/connected -h
 1890  mosquitto_sub -t \$SYS/broker/clients/connected
 1891  mosquitto_sub -t \$SYS/broker/clients/connected -h test.mosqitto.org 1883
 1892  mosquitto_sub -t \$SYS/broker/clients/connected -h test.mosquitto.org 1883
 1893  mosquitto_sub -t \$SYS/broker/clients/connected -h test.mosquitto.org -p 1883
 1894  mosquitto_pub -t desd/classroom/acts1 -q 1 -h  localhost -p 1883 -l -d -m "ajya"                                                   
 1895  mosquitto_pub -t desd/classroom/acts1 -q 1 -h  localhost -p 1883 -d -m "ajya"                                                   
 1896  mosquitto_pub -t desd/classroom/acts1 -q 1 -r --will-topic desd/classroom/acts1 --will-payload "desd 00" -h   localhost -p 1883 -l                                                     
 1897  mosquitto_pub -t desd/classroom/acts1 -q 1 -r --will-topic desd/classroom/acts1 --will-retain  --will-payload "desd 00" -h   localhost -p 1883 -l                                                     
 1898  histroy
 1899  history
 1900  clear
 1901  cd Desktop/
 1902  histroy
 1903  history
 1904  sudo mosquitto_passwd
 1905  sudo mosquitto_passwd -c
 1906  sudo mosquitto_passwd -c /etc/mosquitto/brokerauth desd
 1907  sudo cat /etc/mosquitto/brokerauth 
 1908  cd /etc
 1909  ls
 1910  cd mosquitto/
 1911  ls
 1912  cd conf.d/
 1913  ls
 1914  vo allowall.conf 
 1915  vi allowall.conf 
 1916  sudo vi allowall.conf 
 1917  sudo service mosquitto resatart
 1918  sudo service mosquitto restart
 1919  sudo vi allowall.conf 
 1920  sudo chmod 666 /etc/mosquitto/allowall.conf
 1921  sudo chmod 666 /etc/mosquitto/aclfile.example 
 1922  ls
 1923  sudo service mosquitto restart
 1924  sudo vi allowall.conf 
 1925  sudo service mosquitto restart
 1926  sudo vi allowall.conf 
 1927  sudo service mosquitto restart
 1928  sudo chmod 666 /etc/mosquitto/
 1929  sudo service mosquitto restart
 1930  ls
 1931  cd ..
 1932  ls
 1933  cd ..
 1934  ls
 1935  cd . .
 1936  cd ..
 1937  cd ../\
 1938  cd ../
 1939  sudo chmod 777 /etc/mosquitto/
 1940  cd ..
 1941  ls
 1942  sudo vi mosquitto.conf 
 1943  cd conf.d/
 1944  ls
 1945  sudo vi allowall.conf 
 1946  sudo service mosquitto restart
 1947  clear
 1948  sudo chmod 666  /etc/mosquitto/brokerauth
 1949  sudo service mosquitto restart
 1950  mosquitto_pub -t cdac/desd -h  localhost -p 183 -l -u -p
 1951  mosquitto_pub -t cdac/desd -h  localhost -p 183 -l -u -P
 1952  mosquitto_pub -t cdac/desd -h  localhost -p 183 -l -v -P
 1953  mosquitto_pub -t cdac/desd -h  localhost -p 183 -l -V -P
 1954  mosquitto_pub -t cdac/desd -h  localhost -p 183 -l -u -P
 1955  mosquitto_pub -t cdac/desd -h  localhost -p 1883 -l -u -P 
 1956  mosquitto_pub -t cdac/desd -h  localhost -p 1883 -l -u 
 1957  mosquitto_pub -t cdac/desd -h  localhost -p 1883 -l 
 1958  mosquitto_pub -t cdac/desd -h  localhost -p 1883 -l -v -P 
 1959  mosquitto_pub -t cdac/desd -h  localhost -p 1883 -l -V -P 
 1960  mosquitto_pub -t cdac/desd -u -P -h  localhost -p 1883 -l 
 1961  clear
 1962  mosquitto_pub -t cdac/desd  -h  localhost -p 1883 -l 
 1963  mosquitto_pub -t cdac/desd -u -P -h  localhost -p 1883 -l 
 1964  mosquitto_pub -t cdac/desd -u -P -h  localhost -p 1883 -l  desd
 1965  mosquitto_pub -t cdac/desd -u -P -h  localhost -p 1883 -l  -P desd
 1966  mosquitto_pub -t cdac/desd -u  -h  localhost -p 1883 -l  -P desd
 1967  mosquitto_pub -t cdac/desd -u  -h localhost -p 1883 -l  -P desd
 1968  mosquitto_pub -t cdac/desd  -h localhost -p 1883 -l  -P desd
 1969  mosquitto_pub -t cdac/desd  -h localhost -p 1883 -l -u  -P desd
 1970  mosquitto_pub -t cdac/desd  -h localhost -p 1883 -l -u  -P 
 1971  mosquitto_pub -t cdac/desd  -h localhost -p 1883 -l   -P 
 1972  mosquitto_pub -t cdac/desd  -h localhost -p 1883 -l   -P  desd
 1973  mosquitto_pub -t cdac/desd  -h localhost -p 1883 -l -P desd
 1974  cat /etc/mosquitto/
 1975  ls
 1976  cd ..
 1977  ls
 1978  cat brokerauth 
 1979  cd
 1980  mosquitto_pub -t cdac/desd  -h localhost -p 1883 -l -P desd
 1981  ls -l brokerauth
 1982  cd /etc/mosquitto/
 1983  ls
 1984  ls -l brokerauth
 1985  cd
 1986  mosquitto_pub -t cdac/desd  -h localhost -p 1883 -l -u desd -P desd
 1987  mosquitto_pub -t cdac/desd  -h localhost -q 1 -p 1883 -l -u desd -P desd
 1988  mosquitto_pub -t cdac/desd  -h localhost -q 1 -p 1883 -l -u desd -P desd -d
 1989  mosquitto_pub -t cdac/desd  -h localhost -q 0 -p 1883 -l -u desd -P desd -d


