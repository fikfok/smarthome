from rest_framework import serializers

from models impoer Metrics


class MetricsSerializer(serializers.ModelSerializer):
    class Meta:
        model = Metrics
        fields = ('temperature', 'carbon_dioxide',)

