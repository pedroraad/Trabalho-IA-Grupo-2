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

    void createJsonObjectOfVectors(vector<vector<int>> states , string filename)
    {
        string filePath = "./front/src/" + filename;

        std::ofstream file(filePath);

        if (file.is_open())
        {
            file << "{\n";

            for (int i = 0; i < states.size(); i++)
            {
                file << "\"" << i << "\":";
                string json = vectorToJsonString(states[i]);

                if (i < states.size() - 1)
                {
                    json += ",\n";
                }

                file << json;
            }

            cout << "-----------------------------------------------" << endl;

            file << "\n}\n";

            file.close();
        }
    }
};
