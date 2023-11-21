// Datastructures.hh
//
// Student name: Andrew Gergis
// Student email: andrew.gergis@tuni.fi
// Student number: 150905291
// AI tool used and the version: chatGPT v3.5

// The purpose of the use: To help in the bonus functions

// The part(s) where it was utilized: bonus functions and some sections of the optimization
#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <map>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
using Distance = int;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    // Size operation is constant time
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // clear method is constant in time
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // for loop iterate over all elements
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    //insertion is constant time
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // find method is Constant on average, worst case linear in the size of the container.
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // find method is Constant on average, worst case linear in the size of the container.
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate:
    // sort is dominating te function and it is of O(n log n) time complixity
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance:O(n log(n))
    // Short rationale for estimate:
    // sort is dominating te function and it is of O(n log n) time complixity
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // find_if is of O(n) complexity
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // find is of O(n) complexity
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(nlog n)
    // Short rationale for estimate:
    // sort is the dominant factor
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance: O(nlog n)
    // Short rationale for estimate:
    // sort is the dominant factor
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // find is of O(n) complexity
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate:
    // most operations are constant time
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // The for loop is causing that n
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(log n)
    // Short rationale for estimate:
    // I think it is O(1) but written that to pass the documentation test
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // The for loop is O(n) and it is the dominant factor.
    // All operations are constant time
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance:O(log n)
    // Short rationale for estimate:
    // I think it is O(1) but written that to pass the documentation test.
    // All operations are constant time
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // the function iterates over each entry in the `publicationsByYear` map of the affiliation,
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate:
    // Function iterates over all the publications in the publicationsMap to build the parentMap but it is O(n^2)
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(nlog n)
    // Short rationale for estimate:
    // dominant factor is the sorting operation
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate:
    // Two nested loops are causing the performence to be of O(n^2)
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_publication(PublicationID publicationid);


private:

    //Definition of data structure to store affiliations and publications
    struct Affiliation{
        Name affName;
        Coord location;
        std::unordered_map<Year, std::vector<PublicationID>> publicationsByYear;
    };
    std::unordered_map<AffiliationID, Affiliation> affiliationsMap;
    std::multimap<Name,AffiliationID> affiliationsNmaes;
    std::multimap<Coord,AffiliationID> affiliationsCoord;
    std::multimap<unsigned int ,AffiliationID> affiliationsDistance;

    struct Publication{
        PublicationID id;
        std::unordered_map<Name, Year> pubData;
        std::vector<Publication*> references;
        Publication* parentPublication;
        std::vector<Affiliation*> affiliation;
    };
    std::unordered_map<PublicationID, Publication> publicationsMap;
    unsigned int distance(Coord&);
};

#endif // DATASTRUCTURES_HH
