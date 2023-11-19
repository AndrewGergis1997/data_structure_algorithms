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
    // Create a vector of pairs with affiliation names and IDs
    std::vector<std::pair<Name, AffiliationID>> affiliationPairs;

    // Populate the vector with affiliation names and IDs
    for (const auto& entry : affiliationsMap)
    {
        affiliationPairs.emplace_back(entry.second.affName, entry.first);
    }

    // Sort the vector alphabetically based on affiliation names
    std::sort(affiliationPairs.begin(), affiliationPairs.end());

    // Extract sorted affiliation IDs from the sorted vector
    std::vector<AffiliationID> sortedAffiliations;
    for (const auto& pair : affiliationPairs)
    {
        sortedAffiliations.push_back(pair.second);
    }

    return sortedAffiliations;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    // Create a vector of pairs with affiliation coordinates and IDs
    std::vector<std::pair<Coord, AffiliationID>> affiliationPairs;

    // Populate the vector with affiliation coordinates and IDs
    for (const auto& entry : affiliationsMap)
    {
        affiliationPairs.emplace_back(entry.second.location, entry.first);
    }

    // Sort the vector based on distance and y-value
    std::sort(affiliationPairs.begin(), affiliationPairs.end(),
              [](const auto& a, const auto& b)
    {
        // Calculate Euclidean distances
        auto distanceA = std::sqrt(a.first.x * a.first.x + a.first.y * a.first.y);
        auto distanceB = std::sqrt(b.first.x * b.first.x + b.first.y * b.first.y);

        // Compare distances
        if (distanceA != distanceB)
            return distanceA < distanceB;

        // If distances are equal, compare y-values
        return a.first.y < b.first.y;
    });

    // Extract sorted affiliation IDs from the sorted vector
    std::vector<AffiliationID> sortedAffiliations;
    for (const auto& pair : affiliationPairs)
    {
        sortedAffiliations.push_back(pair.second);
    }

    return sortedAffiliations;
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
    auto it = publicationsMap.find(id);
    if (it != publicationsMap.end()) {
        Publication* publication = &(it->second);
        for (const auto& pair : publicationsMap) {
            for (const auto& reference : pair.second.references) {
                if (reference == publication) {
                    return pair.first; // Found the parent publication
                }
            }
        }
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

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    // Check if the publication with the given ID exists
    auto publicationIt = publicationsMap.find(id);
    if (publicationIt == publicationsMap.end())
    {
        return {NO_PUBLICATION};
    }

    // Vector to store the result
    std::vector<PublicationID> result;

    // Set to keep track of visited publications
    std::unordered_set<PublicationID> visited;

    // Stack to perform depth-first search
    std::vector<PublicationID> stack;
    stack.push_back(id);

    while (!stack.empty())
    {
        PublicationID currentId = stack.back();
        stack.pop_back();

        // Check if the publication has been visited
        if (visited.count(currentId) == 0)
        {
            // Mark the publication as visited
            visited.insert(currentId);

            // Add the current publication ID to the result (except for the initial ID)
            if (currentId != id)
            {
                result.push_back(currentId);
            }

            // Iterate over references and add them to the stack
            for (const auto &ref : publicationsMap[currentId].references)
            {
                stack.push_back(ref->id);
            }
        }
    }
    return result;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    // Vector to store the result
    std::vector<AffiliationID> result;

    // Vector to store the distances and affiliations
    std::vector<std::pair<Distance, AffiliationID>> distances;

    // Calculate distances and fill the distances vector
    for (const auto& [id, affiliation] : affiliationsMap)
    {
        if (affiliation.location.x != NO_VALUE && affiliation.location.y != NO_VALUE)
        {
            Distance distance = static_cast<Distance>(std::sqrt(std::pow(xy.x - affiliation.location.x, 2) +
                                                                std::pow(xy.y - affiliation.location.y, 2)));

            distances.emplace_back(distance, id);
        }
    }

    // Sort the distances vector in increasing order of distance
    std::partial_sort(distances.begin(), distances.begin() + std::min<size_t>(3, distances.size()), distances.end(),
                      [this](const auto& a, const auto& b) {
        return a.first < b.first || (a.first == b.first && affiliationsMap[a.second].location < affiliationsMap[b.second].location);
    });

    // Extract the affiliation IDs from the sorted distances vector
    std::transform(distances.begin(), distances.begin() + std::min<size_t>(3, distances.size()), std::back_inserter(result),
                   [](const auto& pair) { return pair.second; });

    return result;
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

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    auto findAncestors = [&](PublicationID id, std::unordered_set<PublicationID>& ancestors) {
        auto it = publicationsMap.find(id);
        while (it != publicationsMap.end() && it->second.parentPublication) {
            ancestors.insert(it->second.parentPublication->id);
            it = publicationsMap.find(it->second.parentPublication->id);
        }
    };

    std::unordered_set<PublicationID> ancestors1;
    findAncestors(id1, ancestors1);

    std::unordered_set<PublicationID> ancestors2;
    findAncestors(id2, ancestors2);

    // Check if id1 is a parent to id2
    auto it1 = publicationsMap.find(id1);
    if (it1 != publicationsMap.end() && it1->second.parentPublication && ancestors2.count(it1->second.parentPublication->id) > 0) {
        return it1->second.parentPublication->id; // Return the direct parent of the parent (id1)
    }

    // Check if id2 is a parent to id1
    auto it2 = publicationsMap.find(id2);
    if (it2 != publicationsMap.end() && it2->second.parentPublication && ancestors1.count(it2->second.parentPublication->id) > 0) {
        return it2->second.parentPublication->id; // Return the direct parent of the parent (id2)
    }

    // Find the common ancestor
    for (const auto& ancestor : ancestors1) {
        if (ancestors2.count(ancestor) > 0) {
            return ancestor; // Return the common ancestor
        }
    }

    // No common ancestor found
    ancestors1.clear(); // Clean up ancestors1 set
    ancestors2.clear(); // Clean up ancestors2 set
    return NO_PUBLICATION;
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


