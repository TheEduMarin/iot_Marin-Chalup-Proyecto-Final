import json
import boto3

client = boto3.client('iot-data')

def lambda_handler(event, context):
    thing_name = event.get('thing_name')
    if not thing_name:
        return {'statusCode': 400, 'body': 'Missing thing_name'}


    client.publish(
        topic=f"$aws/things/{thing_name}/shadow/update",
        qos=1,
        payload=json.dumps({
            "state": {
                "desired": {
                    "gateState": "open"
                }
            }
        })
    )

    return {
        'statusCode': 200,
        'body': f"Set gateState to open for {thing_name}"
    }
