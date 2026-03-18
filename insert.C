#include "catalog.h"
#include "query.h"

/*
 * Inserts a record into the specified relation.
 *
 * Returns:
 * 	OK on success
 * 	an error code otherwise
 */

const Status QU_Insert(const string &relation,
					   const int attrCnt,
					   const attrInfo attrList[])
{
	cout << "Doing QU_Insert" << endl;
	AttrDesc *attributes;
	int attribute_cnt;
	Status status;

	if ((status = attrCat->getRelInfo(relation, attribute_cnt, attributes)) != OK)
		return status;

	if (attribute_cnt != attrCnt)
		return UNIXERR;

	int reclen = 0;
	for (int i = 0; i < attrCnt; i++)
		reclen += attributes[i].attrLen;

	InsertFileScan ifs(relation, status);
	if (status == OK)
	{

		char *insertData;
		if (!(insertData = new char[reclen]))
			return INSUFMEM;

		int insertOffset = 0;
		int value = 0;
		float fValue = 0;
		for (int i = 0; i < attrCnt; i++)
		{
			bool attrFound = false;
			for (int j = 0; j < attrCnt; j++)
			{
				if (strcmp(attributes[i].attrName, attrList[j].attrName) == 0)
				{
					insertOffset = attributes[i].attrOffset;

					switch (attrList[j].attrType)
					{
					case STRING:
						memcpy((char *)insertData + insertOffset, (char *)attrList[j].attrValue, attributes[i].attrLen);
						break;

					case INTEGER:
						value = atoi((char *)attrList[j].attrValue);
						memcpy((char *)insertData + insertOffset, &value, attributes[i].attrLen);
						break;

					case FLOAT:
						fValue = atof((char *)attrList[j].attrValue);
						memcpy((char *)insertData + insertOffset, &fValue, attributes[i].attrLen);
						break;
					}

					attrFound = true;
					break;
				}
			}

			if (attrFound == false)
			{
				delete[] insertData;
				free(attributes);
				return UNIXERR;
			}
		}

		Record insertRec;
		insertRec.data = (void *)insertData;
		insertRec.length = reclen;

		RID insertRID;
		status = ifs.insertRecord(insertRec, insertRID);

		delete[] insertData;
		free(attributes);

		return status;
	}

	return status;
}
