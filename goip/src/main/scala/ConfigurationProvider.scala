/**
  * Created by bade on 30.05.17..
  */
import play.api.libs.json.{JsValue, Json}

import scala.io.Source

/**
  * Reads configuration from JSON file
  * @todo Abstract it so different config formats (e.g. XML) can be read
  * @param configFilePath Filesystem path to configuration file
  */
class ConfigurationProvider(configFilePath: String) {

  private val jsonFile = Source.fromFile(configFilePath).mkString
  private val json: JsValue = Json.parse(jsonFile)

  /**
    * Gets local port of underlying process
    * @return Local port where the sound is streamed to/from
    */
  def getLocalPort: Int = {
    (json \ "network" \ "localPort").as[Int]
  }
}
