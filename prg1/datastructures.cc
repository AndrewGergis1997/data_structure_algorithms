// Datastructures.cc
//
// Student name: Andrew Gergis
// Student email: andrew.gergis@tuni.fi
// Student number: 150905291

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <unordered_map>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return affiliationsMap.size();
}

void Datastructures::clear_all()
{
    // Clear affiliations data
    affiliationsMap.clear();

    // Clear publications data
    publicationsMap.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{

    std::vector<AffiliationID> allAffiliations;
    allAffiliations.reserve(affiliationsMap.size()); // Reserve space for efficiency

    // Using std::transform with a lambda function to extract the keys (AffiliationIDs)
    std::transform(
                affiliationsMap.begin(), affiliationsMap.end(), std::back_inserter(allAffiliations),
                [](const auto& pair) { return pair.first; }
    );

    return allAffiliations;

}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{

    // Check if the affiliation already exists
    if (affiliationsMap.find(id) != affiliationsMap.end()) {
        return false;  // Affiliation with given ID already exists
    }

    // Affiliation does not exist; add the new affiliation
    affiliationsMap[id] = {name, xy, {}};

    return true;  // Successfully added the affiliation
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    // Use of id to access the affiliation name
    if (affiliationsMap.find(id) != affiliationsMap.end()) {
        return affiliationsMap[id].affName; // Retrieve the name using the id
    }

    // If the ID doesn't exist
    return NO_NAME;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    // Use of id to access the affiliation's coordinates
    if (affiliationsMap.find(id) != affiliationsMap.end()) {
        return affiliationsMap[id].location; // Retrieve the coordinates using the id
    }
    // if the ID doesn't exist
    return NO_COORD;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    std::vector<AffiliationID> affiliationsAlphabetical;
    affiliationsAlphabetical.reserve(affiliationsMap.size());

    // Extracting affiliation IDs and store in a temporary vector
    std::vector<AffiliationID> tempIDs;

    std::transform(affiliationsMap.begin(), affiliationsMap.end(), std::back_inserter(tempIDs),[](const auto& pair) { return pair.first; });

    // Sort the temporary vector alphabetically
    std::sort(tempIDs.begin(), tempIDs.end(), [this](const AffiliationID& a, const AffiliationID& b) {
        return affiliationsMap[a].affName < affiliationsMap[b].affName;
    });

    // Copy the sorted IDs to the final result
    affiliationsAlphabetical = std::move(tempIDs);

    return affiliationsAlphabetical;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<AffiliationID> affiliationsByDistance;
    affiliationsByDistance.reserve(affiliationsMap.size()); // Reserve space for efficiency

    // Create vector of affiliation IDs
    std::vector<AffiliationID> tempIDs;
    std::transform(
                affiliationsMap.begin(), affiliationsMap.end(), std::back_inserter(tempIDs),
                [](const auto& pair) { return pair.first; }
    );

    // Sort the IDs by distance
    std::sort(tempIDs.begin(), tempIDs.end(), [this](const AffiliationID& a, const AffiliationID& b) {
        const Coord& coordA = affiliationsMap[a].location;
        const Coord& coordB = affiliationsMap[b].location;
        // Calculate the distance based on the coordinates (you'll need your distance formula here)
        // Here's an example using Euclidean distance squared for simplicity
        int distanceA = coordA.x * coordA.x + coordA.y * coordA.y;
        int distanceB = coordB.x * coordB.x + coordB.y * coordB.y;
        return distanceA < distanceB;
    });

    // Assign the sorted IDs to the final result
    affiliationsByDistance = std::move(tempIDs);

    return affiliationsByDistance;
}

AffiliationID Datastructures::find_affiliation_with_coord(const Coord xy)
{
    auto it = std::find_if(affiliationsMap.begin(), affiliationsMap.end(), [xy](const auto& pair) {
        return pair.second.location.x == xy.x && pair.second.location.y == xy.y;
    });

    if (it != affiliationsMap.end()) {
        return it->first; // Return the ID of the found affiliation
    }

    return NO_AFFILIATION; // Return a default value if not found
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto it = affiliationsMap.find(id);
    if (it != affiliationsMap.end()) {
        it->second.location = newcoord; // Update the coordinates
        return true; // Affiliation's coordinates updated successfully
    }
    return false; // Affiliation not found
}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
{
    // Check if the publication with the given ID already exists
    auto existingPublication = publicationsMap.find(id);
    if (existingPublication != publicationsMap.end()) {
        return false; // Publication with the given ID already exists
    }

    // Create a new publication
    Publication newPublication;
    newPublication.id = id;
    newPublication.pubData.emplace(name, year);

    // Sort the affiliations vector for binary search
    std::vector<AffiliationID> sortedAffiliations = affiliations;
    std::sort(sortedAffiliations.begin(), sortedAffiliations.end());

    // Process affiliations
    for (const auto& affID : sortedAffiliations) {
        // Find the affiliation using its ID
        auto affiliationIt = affiliationsMap.find(affID);

        // Check if the affiliation with the given ID exists
        if (affiliationIt != affiliationsMap.end()) {
            // Associate the affiliation with the new publication
            newPublication.affiliation.push_back(&(affiliationIt->second));
        }
    }

    // Add the new publication to the data structure
    publicationsMap.emplace(id, std::move(newPublication));

    return true; // Publication added successfully
}

std::vector<PublicationID> Datastructures::all_publications()
{
    std::vector<PublicationID> allPublications;
    allPublications.reserve(publicationsMap.size());

    std::transform(
                publicationsMap.begin(),
                publicationsMap.end(),
                std::back_inserter(allPublications),
                [](const auto& pair) { return pair.first; }
    );

    // Sort the vector of PublicationIDs
    std::sort(allPublications.begin(), allPublications.end());

    return allPublications;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    // Attempt to find the publication based on the given ID
    auto publication = publicationsMap.find(id);

    // Check if the publication exists
    if (publication != publicationsMap.end()) {
        // If found, return the name of the publication
        return publication->second.pubData.begin()->first;
    }

    // If the publication doesn't exist, return the NO_NAME constant
    return NO_NAME;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    // Attempt to find the publication by its ID
    auto publication = publicationsMap.find(id);

    // Check if the publication exists
    if (publication != publicationsMap.end()) {
        // Retrieve the year of the publication
        if (!publication->second.pubData.empty()) {
            return publication->second.pubData.begin()->second;
        }
    }

    // If the publication doesn't exist or has no year data, return the NO_YEAR constant
    return NO_YEAR;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    auto publication = publicationsMap.find(id);

    // Check if the publication exists
    if (publication != publicationsMap.end()) {
        std::vector<AffiliationID> affiliationIDs;

        const Year& publicationYear = publication->second.pubData.begin()->second;

        // Iterate through affiliations and directly access the relevant data
        for (const auto& affiliationPair : affiliationsMap) {
            const Affiliation& affiliation = affiliationPair.second;
            auto foundYear = affiliation.publicationsByYear.find(publicationYear);

            if (foundYear != affiliation.publicationsByYear.end()) {
                auto foundPublication = std::find(foundYear->second.begin(), foundYear->second.end(), id);
                if (foundPublication != foundYear->second.end()) {
                    affiliationIDs.push_back(affiliationPair.first);
                }
            }
        }

        // Sort the vector of affiliation IDs
        std::sort(affiliationIDs.begin(), affiliationIDs.end());

        // Return the list of affiliation IDs associated with the publication
        return affiliationIDs;
    }

    // If the publication doesn't exist, return NO_AFFILIATION
    return {NO_AFFILIATION};
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    auto publication = publicationsMap.find(id);
    auto parentPublication = publicationsMap.find(parentid);

    if (publication != publicationsMap.end() && parentPublication != publicationsMap.end()) {
        parentPublication->second.references.push_back(&publication->second);
        publication->second.parentPublication = &parentPublication->second;
        return true; // Reference added successfully
    }

    return false; // One or both publications not found
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    // Check if the publication with the given ID exists
    if (!publicationsMap.count(id)) {
        return {NO_PUBLICATION};
    }

    // Retrieve the publication object
    const Publication& publication = publicationsMap.at(id);

    // Extract the publication IDs from the references
    std::vector<PublicationID> directReferences;
    for (const Publication* reference : publication.references) {
        directReferences.push_back(reference->id);
    }

    return directReferences;
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    auto affIt = affiliationsMap.find(affiliationid);
    if (affIt == affiliationsMap.end()) {
        return false; // Affiliation not found
    }

    auto pubIt = publicationsMap.find(publicationid);
    if (pubIt == publicationsMap.end()) {
        return false; // Publication not found
    }

    // Add the affiliation to the publication
    affIt->second.publicationsByYear[pubIt->second.pubData.begin()->second].push_back(publicationid);
    pubIt->second.affiliation.push_back(&affIt->second);

    return true;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    auto affiliationIt = affiliationsMap.find(id);

    if (affiliationIt != affiliationsMap.end()) {
        const Affiliation& affiliation = affiliationIt->second;
        std::vector<PublicationID> result;

        for (const auto& entry : affiliation.publicationsByYear) {
            const std::vector<PublicationID>& publicationIds = entry.second;
            result.insert(result.end(), publicationIds.begin(), publicationIds.end());
        }

        return result;
    }

    return {NO_PUBLICATION};
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    // Check if the publication with the given ID exists
     auto it = publicationsMap.find(id);
     if (it != publicationsMap.end()) {
         // Retrieve the publication object
         const Publication& publication = it->second;

         // Check if the publication has a parent
         if (publication.parentPublication != nullptr) {
             return publication.parentPublication->id;
         }

         // Use a hash table to store the parent-child relationships between publications
         std::unordered_map<PublicationID, PublicationID> parentMap;

         // Populate the parent map by iterating through all publications
         for (const auto& pair : publicationsMap) {
             const Publication& currentPublication = pair.second;

             for (Publication* child : currentPublication.references) {
                 parentMap[child->id] = currentPublication.id;
             }
         }

         // Follow the chain of parent-child relationships until we reach a publication with no parent
         PublicationID currentID = id;
         while (parentMap.count(currentID) > 0) {
             currentID = parentMap[currentID];
         }

         return currentID; // Found the parent publication
     }

     return NO_PUBLICATION; // If there's no parent publication
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    if (affiliationsMap.find(affiliationid) == affiliationsMap.end()) {
        return {{NO_YEAR, NO_PUBLICATION}};
    }

    std::vector<std::pair<Year, PublicationID>> publicationsAfterYear;

    const Affiliation& affiliation = affiliationsMap[affiliationid];
    for (const auto& [pubYear, pubIDs] : affiliation.publicationsByYear) {
        if (pubYear >= year) {
            for (PublicationID pubID : pubIDs) {
                publicationsAfterYear.emplace_back(pubYear, pubID);
            }
        }
    }

    std::sort(publicationsAfterYear.begin(), publicationsAfterYear.end(),
              [](const auto& a, const auto& b) {
        return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second);
    });

    return publicationsAfterYear;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    std::vector<PublicationID> referencedByChain;

    if (publicationsMap.find(id) == publicationsMap.end()) {
        return {NO_PUBLICATION};
    }

    std::queue<PublicationID> publicationQueue;
    std::unordered_map<PublicationID, bool> visited;

    publicationQueue.push(id);

    while (!publicationQueue.empty()) {
        PublicationID currentID = publicationQueue.front();
        publicationQueue.pop();

        if (visited[currentID]) {
            continue;
        }

        visited[currentID] = true;

        const Publication& publication = publicationsMap[currentID];

        for (const auto& [pubID, pub] : publicationsMap) {
            if (pub.references.end() != std::find(pub.references.begin(), pub.references.end(), &publication)) {
                if (!visited[pubID]) {
                    publicationQueue.push(pubID);
                    referencedByChain.push_back(pubID);
                }
            }
        }
    }
    return referencedByChain;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations_closest_to()");
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations_closest_to()");
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    auto affiliationIter = affiliationsMap.find(id);

    if (affiliationIter == affiliationsMap.end()) {
        return false; // Affiliation with the given ID doesn't exist
    }

    // Remove the affiliation's association from publications
    for (auto& publication : publicationsMap) {
        auto& affiliationVector = publication.second.affiliation;
        affiliationVector.erase(std::remove(affiliationVector.begin(), affiliationVector.end(), &affiliationIter->second), affiliationVector.end());
    }

    affiliationsMap.erase(affiliationIter);
    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID /*id1*/, PublicationID /*id2*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_closest_common_parent()");
}


bool Datastructures::remove_publication(PublicationID publicationid)
{
    auto publicationIter = publicationsMap.find(publicationid);

    if (publicationIter == publicationsMap.end()) {
        return false; // Publication with the given ID doesn't exist
    }

    // Remove the references to this publication from other publications
    for (auto& publication : publicationsMap) {
        auto& references = publication.second.references;
        references.erase(std::remove(references.begin(), references.end(), &publicationIter->second), references.end());
    }

    // Clear the affiliation reference of the publication
    for (auto& affiliation : publicationIter->second.affiliation) {
        auto& publicationsByYear = affiliation->publicationsByYear;

        for (auto& [year, pubIDs] : publicationsByYear) {
            pubIDs.erase(std::remove(pubIDs.begin(), pubIDs.end(), publicationid), pubIDs.end());
        }
    }
    publicationIter->second.affiliation.clear();

    // Erase the publication
    publicationsMap.erase(publicationIter);
    return true;
}


