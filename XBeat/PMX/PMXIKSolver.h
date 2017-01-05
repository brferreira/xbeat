#pragma once

#include <Urho3D/Urho3D.h>
#include <Urho3D/Container/Vector.h>
#include <Urho3D/Scene/LogicComponent.h>

#include <vector>

class PMXIKNode;

class PMXIKSolver
	: public Urho3D::LogicComponent
{
	URHO3D_OBJECT(PMXIKSolver, Urho3D::LogicComponent);

public:
	PMXIKSolver(Urho3D::Context *context);
	~PMXIKSolver();
	/// Register object factory.
	static void RegisterObject(Urho3D::Context* context);

	virtual void FixedUpdate(float timeStep);

	void AddNode(PMXIKNode *node);

	void SetThreshold(float value) { threshold = value; }
	void SetAngleLimit(float limit) { angleLimit = limit; }
	void SetLoopCount(int count) { loopCount = count; }
	void SetEndNode(Urho3D::Node *node) { endNode = node; }

	float GetThreshold() const { return threshold; }
	float GetAngleLimit() const { return angleLimit; }
	int GetLoopCount() const { return loopCount; }
	Urho3D::Node* GetEndNode() const { return endNode; }

private:
    void SolveForward(const Urho3D::Vector3 &destination);
    void SolveBackward(const Urho3D::Vector3 &destination);
	void PerformInnerIteration(const Urho3D::Vector3 &parentPosition, Urho3D::Vector3 &linkPosition, Urho3D::Vector3 &targetPosition, PMXIKNode* link);

	float threshold;
	float angleLimit;
	int loopCount;
	Urho3D::Node *endNode;
	std::vector<PMXIKNode*> nodes;
    std::vector<Urho3D::Matrix3x4> cachedNodeTransforms;
};
