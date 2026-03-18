#include "catalog.h"
#include "query.h"
#include "error.h"

/*
 * Deletes records from a specified relation.
 *
 * Parameters:
 *  - relation: name of the relation (table) to delete from
 *  - attrName: name of the attribute to filter on (can be empty for unconditional delete)
 *  - op: comparison operator (e.g., EQ, LT, GT, etc.)
 *  - type: datatype of the attribute (INTEGER, FLOAT, STRING)
 *  - attrValue: string representation of the value to compare against
 *
 * Returns:
 * 	OK on success
 * 	an error code otherwise
 */

const Status QU_Delete(const string &relation,
                       const string &attrName,
                       const Operator op,
                       const Datatype type,
                       const char *attrValue)
{
    cout << "Doing QU_Delete" << endl;

    Status status;
    RID rid;
    // Initialize a HeapFileScan to scan through the relation

    HeapFileScan scan(relation, status); // creates scanner over the relation
    if (status != OK)
        return status;

    // Unconditional delete:
    if (attrName.empty())
    {   // check if condition specified
        status = scan.startScan(0, 0, STRING, NULL, EQ); // dummy scan
        if (status != OK)
            return status;
    }
    else
    {
        // Get attribute metadata
        AttrDesc attr;
        status = attrCat->getInfo(relation, attrName, attr);
        if (status != OK)
            return status;

        // Prepare the value to compare with, depending on the type
        const void *filterValue = nullptr;
        int intVal;
        float floatVal;

        // Convert attrValue to correct type
        if (type == INTEGER)
        {
            intVal = atoi(attrValue); // Convert string to int
            filterValue = &intVal;
        }
        else if (type == FLOAT)
        {
            floatVal = atof(attrValue); // Convert string to float
            filterValue = &floatVal;
        }
        else if (type == STRING)
        {
            filterValue = attrValue; // Use the string directly
        }
        else
        {
            return TMP_RES_EXISTS;  // Unsupported type
        }

        // Start filtered scan
        status = scan.startScan(attr.attrOffset, attr.attrLen, type, static_cast<const char *>(filterValue), op);
        if (status != OK)
            return status;
    }

    // Delete matching records
    while ((status = scan.scanNext(rid)) == OK)
    {
        Status delStatus = scan.deleteRecord(); // Delete current record
        if (delStatus != OK)
        {
            scan.endScan(); // Cleanup before returning error
            return delStatus;
        }
    }

    // Check if scan finished normally
    if (status != FILEEOF)
    { // end of file and clean up
        scan.endScan();
        return status;
    }

    // Cleanup and success
    return scan.endScan();
}
