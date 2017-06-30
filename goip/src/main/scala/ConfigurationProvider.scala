/**
  * Created by bade on 30.05.17..
  */
import play.api.libs.json.{JsValue, Json}

import scala.io.Source

class ConfigurationProvider(configFile: String) {

  private val jsonFile = Source.fromFile(configFile).mkString
  private val json: JsValue = Json.parse(jsonFile)

  def getLocalPort: Int = {
    (json \ "network" \ "localPort").as[Int]
  }
}
