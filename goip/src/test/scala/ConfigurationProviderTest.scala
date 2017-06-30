import org.scalatest.FunSuite

/**
  * Created by bade on 30.06.17..
  */
class ConfigurationProviderTest extends FunSuite {

  test("A function should parse the port number") {

    val port = new ConfigurationProvider("./src/test/resources/config.json").getLocalPort

    assert(port == 1337)
  }

}
