#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Util
{
private:
public:
    Util()
    {
    }

    string vectorToJsonString(const vector<int> &myVector)
    {
        string jsonString = "[";

        for (size_t i = 0; i < myVector.size(); ++i)
        {
            jsonString += to_string(myVector[i]);

            // Add a comma if not the last element
            if (i < myVector.size() - 1)
            {
                jsonString += ",";
            }
        }

        jsonString += "]";

        return jsonString;
    }

    void createJsonFileResult(vector<int> states, string filename, int boardOrder)
    {
        string filePath = "./front/src/" + filename;

        std::ofstream file(filePath);

        if (file.is_open())
        {
            file << "{\n";

            file << "\"boardOrder\":";
            file << boardOrder;
            file << ",\n";

            file << "\"data\" :" ;
  

            string json = vectorToJsonString(states);

            file << json;

            cout << "-----------------------------------------------" << endl;

            file << "\n}\n";

            file.close();
        }
    }
};
