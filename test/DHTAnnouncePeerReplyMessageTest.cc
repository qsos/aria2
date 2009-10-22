#include "DHTAnnouncePeerReplyMessage.h"

#include <cppunit/extensions/HelperMacros.h>

#include "DHTNode.h"
#include "Exception.h"
#include "Util.h"
#include "bencode.h"

namespace aria2 {

class DHTAnnouncePeerReplyMessageTest:public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(DHTAnnouncePeerReplyMessageTest);
  CPPUNIT_TEST(testGetBencodedMessage);
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp() {}

  void tearDown() {}

  void testGetBencodedMessage();
};


CPPUNIT_TEST_SUITE_REGISTRATION(DHTAnnouncePeerReplyMessageTest);

void DHTAnnouncePeerReplyMessageTest::testGetBencodedMessage()
{
  SharedHandle<DHTNode> localNode(new DHTNode());
  SharedHandle<DHTNode> remoteNode(new DHTNode());

  unsigned char tid[DHT_TRANSACTION_ID_LENGTH];
  util::generateRandomData(tid, DHT_TRANSACTION_ID_LENGTH);
  std::string transactionID(&tid[0], &tid[DHT_TRANSACTION_ID_LENGTH]);

  DHTAnnouncePeerReplyMessage msg(localNode, remoteNode, transactionID);

  std::string msgbody = msg.getBencodedMessage();

  BDE dict = BDE::dict();
  dict["t"] = transactionID;
  dict["y"] = BDE("r");
  BDE rDict = BDE::dict();
  rDict["id"] = BDE(localNode->getID(), DHT_ID_LENGTH);
  dict["r"] = rDict;

  CPPUNIT_ASSERT_EQUAL(bencode::encode(dict), msgbody);
}

} // namespace aria2
