#include <sstream>
#include "KDNode.hh"
#include "../../tools/Tools.hh"

KDNode::KDNode(std::vector<Polygon> &polygonsVect, const BoundingBox &box) {
    /* Constructor initialization */
    splitAxis_ = box.GetLargestDimension();
    Polygon::setComparisonfactor(splitAxis_);
    box_ = std::make_shared<BoundingBox>(box);
    polygons_ = std::make_shared<std::vector<Polygon>>();
    if (polygonsVect.empty())
        return;
    splitValue_ = polygonsVect.at(polygonsVect.size() / 2).getMeanOfInterest();
    /* End Constructor initialization */
    std::sort(polygonsVect.begin(), polygonsVect.end());
    auto underList = std::vector<Polygon>();
    auto aboveList = std::vector<Polygon>();
    for (const auto &polygon: polygonsVect) {
        float mmin, mmax;
        polygon.getBoundsOfInterest(mmin, mmax);
        if (mmin > splitValue_) {
            aboveList.push_back(polygon);
            continue;
        }
        if (mmax < splitValue_) {
            underList.push_back(polygon);
            continue;
        }
        polygons_->push_back(polygon);
    }
    if (!underList.empty()) {
        BoundingBox b;
        Tools<float>::extremumPolygonList(underList, b);
        left_ = std::make_shared<KDNode>(underList, b);

    }
    if (!aboveList.empty()) {
        BoundingBox b;
        Tools<float>::extremumPolygonList(aboveList, b);
        right_ = std::make_shared<KDNode>(underList, b);
    }


}

void KDNode::printInfix(unsigned id, bool isleft) {

    std::ostringstream nodeName("");


    nodeName << "id:" << id << " ";

    switch (splitAxis_) {
        case SplitAxis::X :
            nodeName << "X";
            break;
        case SplitAxis::Y :
            nodeName << "Y";
            break;
        case SplitAxis::Z :
            nodeName << "Z";
            break;
        default:
            nodeName << "none";
    }
    nodeName << " val:" << splitValue_ << " size:" << polygons_->size();

    std::string name = "\"" + nodeName.str() + "\"";
    if (id > 0)
        std::cout << name << ";\n";

    if (left_) {
        std::cout << name << " -> ";
        left_->printInfix(id * 2, true);
    }

    if (right_) {
        std::cout << name << " -> ";
        right_->printInfix(id * 2 + 1, false);
    }

}
