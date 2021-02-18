// Copyright 1996-2021 Cyberbotics Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Implemented node class representing an transmission joint

#ifndef WB_TRANSMISSION_JOINT_HPP
#define WB_TRANSMISSION_JOINT_HPP

#include "WbBaseNode.hpp"
#include "WbHingeJoint.hpp"

class WbBoundingSphere;

class WbTransmissionJoint : public WbHingeJoint {
  Q_OBJECT

public:
  explicit WbTransmissionJoint(const QString &modelName, WbTokenizer *tokenizer = NULL);
  explicit WbTransmissionJoint(WbTokenizer *tokenizer = NULL);
  WbTransmissionJoint(const WbTransmissionJoint &other);
  explicit WbTransmissionJoint(const WbNode &other);
  virtual ~WbTransmissionJoint();

  void preFinalize() override;
  void postFinalize() override;
  int nodeType() const override { return WB_NODE_TRANSMISSION_JOINT; }
  void createWrenObjects() override;
  void prePhysicsStep(double ms) override;
  void postPhysicsStep() override;
  void reset() override;
  void resetPhysics() override;
  void save() override;
  QVector<WbLogicalDevice *> devices() const override;
  bool resetJointPositions() override;
  void setPosition(double position, int index = 1) override;
  double position(int index = 1) const override;
  double initialPosition(int index = 1) const override;
  WbHingeJointParameters *hingeJointParameters2() const;
  void computeStartPointSolidPositionFromParameters(WbVector3 &translation, WbRotation &rotation) const;

  void setSolidStartPoint(WbSolid *solid);
  void setSolidStartPoint(WbSolidReference *solid);
  void setSolidStartPoint(WbSlot *slot);
  WbSolid *solidStartPoint() const;
  WbSolidReference *solidReference() const;

public slots:
  bool setJoint() override;
  bool setJoint2();

  void updateStartPoint();

signals:
  void startPointChanged(WbBaseNode *node);

protected:
  virtual WbVector3 axis2() const;  // return the axis of the joint with coordinates relative to the parent Solid; defaults to
                                    // the rotation axis of the solid endpoint
  virtual WbVector3 anchor2() const;

  dJointID mJoint2;
  dJointID jointID() const { return mJoint2; }
  WbQuaternion endPointRotation() const;
  WbRotationalMotor *rotationalMotor2() const;
  double mOdePositionOffset2;
  double mPosition2;                       // Keeps track of the joint position2 if JointParameters2 don't exist.
  bool mSpringAndDampingConstantsAxis1On;  // defines if there is spring and dampingConstant along this axis
  bool mSpringAndDampingConstantsAxis2On;
  double mInitialPosition2;
  void updatePosition(double position) override;
  void updatePosition2(double position);
  void updateEndPointZeroTranslationAndRotation() override;
  void updateStartPointZeroTranslationAndRotation();
  void applyToOdeSpringAndDampingConstants(dBodyID body, dBodyID parentBody) override;
  void updateOdePositionOffset() override;
  void updateOdePositionOffset2();
  void writeExport(WbVrmlWriter &writer) const override;
  bool mIsStartPointPositionChangedByJoint;
  WbVector3 mStartPointZeroTranslation;
  WbRotation mStartPointZeroRotation;
  void retrieveStartPointSolidTranslationAndRotation(WbVector3 &it, WbRotation &ir) const;

protected slots:
  void updateParameters() override;
  void updatePosition() override;
  void updatePosition2();
  void updateJointAxisRepresentation() override;
  void updateAxis() override;
  void updateAxis2();
  void updateAnchor() override;
  void updateAnchor2();

private:
  enum { UNDEFINED, CLASSIC_GEAR, BEVEL_GEAR, CHAIN_DRIVE };
  int mGearType;
  void inferGearType();
  WbTransmissionJoint &operator=(const WbTransmissionJoint &);  // non copyable
  void updateParameters2();
  void init();
  WbSFNode *mParameters2;
  WbSFNode *mStartPoint;
  WbSFDouble *mBacklash;
  WbSFDouble *mMultiplier;
  void updateBacklash();
  void updateMultiplier();
  void applyToOdeAxis() override;
  void applyToOdeAxis2();
  void applyToOdeAnchor2();

private slots:
  void updateStartPointPosition();
  void updateBoundingSphere(WbBaseNode *subNode);
};

#endif
