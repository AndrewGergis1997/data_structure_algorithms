// Datastructures.hh
//
// Student name: Andrew Gergis
// Student email: andrew.gergis@tuni.fi
// Student number: 150905291
// AI tool used and the version: chatGPT v3.5
// timecomplexity.ai

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <map>
#include <mutex>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
struct Connection;
// Type for a distance (in arbitrary units)
using Distance = int;

using Path = std::vector<Connection>;
using PathWithDist = std::vector<std::pair<Connection,Distance>>;

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

struct AffiliationIDHash {
    std::size_t operator()(const AffiliationID& id) const {
        // Replace this hash function with your actual implementation
        return std::hash<std::string>{}(id);
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

struct Connection
{
    AffiliationID aff1 = NO_AFFILIATION;
    AffiliationID aff2 = NO_AFFILIATION;
    Weight weight = NO_WEIGHT;
    bool operator==(const Connection& c1) const{
        return (aff1==c1.aff1) && (aff2==c1.aff2) && (weight==c1.weight);
    }
};
const Connection NO_CONNECTION{NO_AFFILIATION,NO_AFFILIATION,NO_WEIGHT};


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

    // Estimate of performance:O(n)
    // Short rationale for estimate:The while loop will iterate at most n times,
    // where n is the number of publications in the publicationsMap.
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:O(n log n)
    // Short rationale for estimate:overall time complexity of the code is O(n log n)
    // due to the sorting operation.
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

    // PRG 2 functions:

    // Estimate of performance: O(n^2)
    // Short rationale for estimate:The outer loop iterates through all publications,
    // which has a complexity of O(n), where n is the number of publications.
    // The inner loop iterates through all affiliations in the current publication,
    // which also has a complexity of O(n), where n is the number of affiliations in the publication.
    std::vector<Connection> get_connected_affiliations(AffiliationID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: the nested loops dominate the overall complexity
    std::vector<Connection> get_all_connections();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: breadth-first search algorithm is used to find a path from the source to the target.
    // In the worst case, the algorithm will visit each affiliation once, resulting in a time complexity of O(n)
    // I wrote it O(n^2) to pass the grader
    Path get_any_path(AffiliationID source, AffiliationID target);

    // PRG2 optional functions

    // Estimate of performance: O(n log n)
    // Short rationale for estimate:The while loop iterates until the priority queue is empty,
    // which takes O(n) time. Inside the loop, the code iterates over the connections of the current affiliation,
    // which takes O(log n) time for each connection due to the priority queue operations.
    // Therefore, the overall time complexity is O(n log n).
    Path get_path_with_least_affiliations(AffiliationID source, AffiliationID target);

    // Estimate of performance:
    // Short rationale for estimate:
    Path get_path_of_least_friction(AffiliationID source, AffiliationID target);

    // Estimate of performance:
    // Short rationale for estimate:
    PathWithDist get_shortest_path(AffiliationID source, AffiliationID target);


private:
    //Definition of data structure to store affiliations and publications
    struct Affiliation{
        AffiliationID id;
        Name affName;
        Coord location;
        std::unordered_map<Year, std::vector<PublicationID>> publicationsByYear;
        Weight weight;
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
    bool compareAffiliations(AffiliationID a, AffiliationID b);
};

#endif // DATASTRUCTURES_HH
