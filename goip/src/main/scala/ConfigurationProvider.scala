/**
  * Created by bade on 30.05.17..
  */
import play.api.libs.json.{JsValue, Json}

import scala.io.Source

object ConfigurationProvider {

  private val jsonFile = Source.fromFile("../config/config.json").mkString
  private val json: JsValue = Json.parse(jsonFile)

  def getLocalPort: Int = {
    (json \ "network" \ "localPort").as[Int]
  }
}
