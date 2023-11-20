g++ -g -std=c++11 -o arq.exe ./src/**.cpp
if [ $? -eq 0 ];then 
   echo "Compilado com sucesso!"
   ./arq.exe 
else
   echo "Não compilado..."
fi